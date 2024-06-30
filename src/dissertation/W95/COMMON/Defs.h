//---------------------------------------------------------------------------
#ifndef DefsH
#define DefsH
//---------------------------------------------------------------------------

#define NET_FILE_EXT  ".n"
#define PTN_FILE_EXT  ".p"
#define PTN2_FILE_EXT ".p2"

#define FILE_ID_SIZE   64
#define NET_FILE_ID  "N2 NET CFG FILE"
#define PTN_FILE_ID  "N2 PATTERN FILE"
#define PTN2_FILE_ID "N2 RECOGNITION PTN FILE"

#define MAX_CONNECTIONS_ALLOWED 16
#define SERVER_PORT             8888
#define WINSOCK_MAJOR           1
#define WINSOCK_MINOR           1
#define UNK_PINGTIME            1000000
#define PACKET_SIZE             64

#define CMD_NET_CFG "NCFG"
#define CMD_START   "Go!!"
#define CMD_PING    "PING"
#define CMD_INFO    "INFO"
#define CMD_READY   "RDY "      // pentru ponderi - serverul e gata de receptie/transmisie
#define CMD_NREADY  "NRDY"      // analog

#define WRONG_REPLY_ID 1024
#define WRONG_PING_ID  1025
#define WSA_START_ERR  1026
#define WRONG_PACKET_SIZE 1027
#define WRONG_INFO_ID  1028
#define WRONG_ACK      1029
#define WRONG_DATA_PTR 1030

#define MAX_MESSAGES 256

enum TActivation {act_sigmoid, act_2p_sigmoid, act_arctan, act_linear};

typedef struct
{
  char processor[32];
  float  speed;  // milioane operatii pe secunda
  int  memoryTotal, memoryFree;
  char os[192];
  int  minorVersion, majorVersion;
  char computerName[64], userName[64];
} TRemoteMachineInfo;

typedef struct
{
  int inputsNo;
  int hiddenNo;
  int outputsNo;
  int iMin, iMax;
  int hMin, hMax;
  int oMin, oMax;
  float learningRate;
  bool  isMomentumTerm;
  float momentumTerm;
  int   saveCount;
  bool  hasBeenTrained;
} TPartitionInfo;

#endif
