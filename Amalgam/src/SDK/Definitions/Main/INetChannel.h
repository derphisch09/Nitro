#pragma once
#include "NetChannel.h"
#include "INetChannelInfo.h"
#include "INetMessage.h"

class IDemoRecorder;
class INetChannelHandler;

class INetChannel : public INetChannelInfo
{
public:
	virtual	~INetChannel(void) {};
	virtual void SetDataRate(float rate) = 0;
	virtual bool RegisterMessage(INetMessage* msg) = 0;
	//virtual bool StartStreaming(unsigned int challengeNr) = 0;
	//virtual void ResetStreaming(void) = 0;
	virtual void SetTimeout(float seconds) = 0;
	virtual void SetDemoRecorder(IDemoRecorder* recorder) = 0;
	virtual void SetChallengeNr(unsigned int chnr) = 0;
	virtual void Reset(void) = 0;
	virtual void Clear(void) = 0;
	virtual void Shutdown(const char* reason) = 0;
	virtual void ProcessPlayback(void) = 0;
	//virtual bool ProcessStream(void) = 0;
	virtual void ProcessPacket(struct netpacket_s* packet, bool bHasHeader) = 0;
	virtual bool SendNetMsg(INetMessage& msg, bool bForceReliable = false, bool bVoice = false) = 0;
	virtual bool SendData(bf_write& msg, bool bReliable = true) = 0;
	virtual bool SendFile(const char* filename, unsigned int transferID) = 0;
	virtual void DenyFile(const char* filename, unsigned int transferID) = 0;
	virtual void RequestFile_OLD(const char* filename, unsigned int transferID) = 0;
	virtual void SetChoked(void) = 0;
	virtual int SendDatagram(bf_write* data) = 0;
	virtual bool Transmit(bool onlyReliable = false) = 0;
	virtual const netadr_t& GetRemoteAddress(void) const = 0;
	virtual INetChannelHandler* GetMsgHandler(void) const = 0;
	virtual int GetDropNumber(void) const = 0;
	virtual int GetSocket(void) const = 0;
	virtual unsigned int GetChallengeNr(void) const = 0;
	virtual void GetSequenceData(int& nOutSequenceNr, int& nInSequenceNr, int& nOutSequenceNrAck) = 0;
	virtual void SetSequenceData(int nOutSequenceNr, int nInSequenceNr, int nOutSequenceNrAck) = 0;
	virtual void UpdateMessageStats(int msggroup, int bits) = 0;
	virtual bool CanPacket(void) const = 0;
	virtual bool IsOverflowed(void) const = 0;
	virtual bool IsTimedOut(void) const = 0;
	virtual bool HasPendingReliableData(void) = 0;
	virtual void SetFileTransmissionMode(bool bBackgroundMode) = 0;
	virtual void SetCompressionMode(bool bUseCompression) = 0;
	virtual unsigned int RequestFile(const char* filename) = 0;
	virtual float GetTimeSinceLastReceived(void) const = 0;
	virtual void SetMaxBufferSize(bool bReliable, int nBytes, bool bVoice = false) = 0;
	virtual bool IsNull() const = 0;
	virtual int GetNumBitsWritten(bool bReliable) = 0;
	virtual void SetInterpolationAmount(float flInterpolationAmount) = 0;
	virtual void SetRemoteFramerate(float flFrameTime, float flFrameTimeStdDeviation) = 0;
	virtual void SetMaxRoutablePayloadSize(int nSplitSize) = 0;
	virtual int GetMaxRoutablePayloadSize() = 0;
	virtual int GetProtocolVersion() = 0;
};

typedef void* FileHandle_t;

class CNetChannel : public INetChannel
{
	typedef struct dataFragments_s
	{
		FileHandle_t file;                 // open file handle
		char         filename[260]; // filename
		char* buffer;               // if NULL it's a file
		unsigned int BYTEs;                // size in BYTEs
		unsigned int bits;                 // size in bits
		unsigned int transferID;           // only for files
		bool         isCompressed;         // true if data is bzip compressed
		unsigned int nUncompressedSize;    // full size in BYTEs
		bool         asTCP;                // send as TCP stream
		int          numFragments;         // number of total fragments
		int          ackedFragments;       // number of fragments send & acknowledged
		int          pendingFragments;     // number of fragments send, but not acknowledged yet
	} dataFragments_t;

	struct subChannel_s
	{
		int startFraggment[MAX_STREAMS];
		int numFragments[MAX_STREAMS];
		int sendSeqNr;
		int state; // 0 = free, 1 = scheduled to send, 2 = send & waiting, 3 = dirty
		int index; // index in m_SubChannels[]
	};

	typedef struct netframe_s
	{
		float          time;        // net_time received/send
		int            size;        // total size in BYTEs
		float          latency;     // raw ping for this packet, not cleaned. set when acknowledged otherwise -1.
		float          avg_latency; // averaged ping for this packet
		bool           valid;       // false if dropped, lost, flushed
		int            choked;      // number of previously chocked packets
		int            dropped;
		float          m_flInterpolationAmount;
		unsigned short msggroups[TOTAL]; // received BYTEs for each message group
	} netframe_t;

	typedef struct
	{
		float       nextcompute;      // Time when we should recompute k/sec data
		float       avgBYTEspersec;   // average BYTEs/sec
		float       avgpacketspersec; // average packets/sec
		float       avgloss;          // average packet loss [0..1]
		float       avgchoke;         // average packet choke [0..1]
		float       avglatency;       // average ping, not cleaned
		float       latency;          // current ping, more accurate also more jittering
		int         totalpackets;     // total processed packets
		int         totalBYTEs;       // total processed BYTEs
		int         currentindex;     // current frame index
		netframe_t  frames[64];       // frame history
		netframe_t* currentframe;     // current frame
	} netflow_t;

	typedef struct netpacket_s
	{
		netadr_t		from;		// sender IP
		int				source;		// received source 
		double			received;	// received time
		unsigned char* data;		// pointer to raw packet data
		bf_read			message;	// easy bitbuf data access
		int				size;		// size in bytes
		int				wiresize;   // size in bytes before decompression
		bool			stream;		// was send as stream
		struct netpacket_s* pNext;	// for internal use, should be NULL in public
	} netpacket_t;

public:
	virtual ConnectionStatus_t GetConnectionState();
	virtual const netadr_t& GetRemoteAddress(void) const;

	ConnectionStatus_t m_ConnectionState;
	int m_nOutSequenceNr;
	int m_nInSequenceNr;
	int m_nOutSequenceNrAck;
	int m_nOutReliableState;
	int m_nInReliableState;
	int m_nChokedPackets;
	int m_PacketDrop;
	bf_write m_StreamReliable;
	byte m_ReliableDataBuffer[8 * 1024];
	CUtlVector<byte> m_ReliableDataBufferMP;
	bf_write m_StreamUnreliable;
	byte m_UnreliableDataBuffer[NET_MAX_DATAGRAM_PAYLOAD];
	CUDPSocket* m_pSocket;
	int m_StreamSocket;
	unsigned int m_MaxReliablePayloadSize;
	netadr_t remote_address;
	float last_received;
	float connect_time;
	int m_Rate;
	float m_fClearTime;
	float m_Timeout;
	char m_Name[32];
	INetworkMessageHandler* m_MessageHandler;
};