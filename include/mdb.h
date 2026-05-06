#ifndef MDB_H
#define	MDB_H

#ifdef	__cplusplus
extern "C" {
#endif

    //------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

#define MAX_MSG_LEN 36+1  // section 2.2

#define ADDRESS_MASK      0xF8  // section 2.3 - top five bits of address are actually address
#define COMMAND_MASK      0x07  // section 2.3 - bottom three bits are command


// Address of each device section 2.2
#define ADDRESS_VMC       0x00
#define ADDRESS_CHANGER   0x08

#define ADDRESS_COIN1     0x58  // Coin Hopper 1
#define ADDRESS_CD2       0x60  // Cashless Device 2
#define ADDRESS_AVD       0x68  // Age Verification Device
#define ADDRESS_COIN2     0x70  // Coin Hopper 2
// higher addresses are for future expansion


// section 2.2
#define MDB_MSG_ACK  0x00  // ack
#define MDB_MSG_RET  0xAA  // please retransmit last byte
#define MDB_MSG_NAK  0xFF  // negative ack


// Secuencia de comandos
#define MDB_CMD_RESET_08 0x08        // Command for changer to self-reset.
#define MDB_CMD_SETUP_09 0x09        // Request for changer setup information.
#define MDB_CMD_TUBE_STATUS_0A 0x0A  // Request for changer tube status.
#define MDB_CMD_POLL_0B 0x0B         // Request for changer activity status.
#define MDB_CMD_COIN_TYPE_0C 0x0C    // Signifies coin types accepted and allowable coin dispensing.
                                     // This command is followed by setup data.
#define MDB_CMD_DISPENSE_0D 0x0D     // Command to dispense a coin type.
                                     // Followed by coin type to dispense.
#define MDB_CMD_EXPANSION_0F 0x0F    // Command to allow addition of features and future enhancements.



/*  Respuestas del monedero  */
#define CHANGER_EXPANSION_IDENTIFICATION_COMMAND 0x00

#define CHANGER_POLL_RESPONSE_COINSDISPENSEDMANUALLY 0x80
#define CHANGER_POLL_RESPONSE_COINSDEPOSITED 0x40
#define CHANGER_POLL_RESPONSE_STATUS 0x00
#define CHANGER_POLL_RESPONSE_SLUG 0x20

#define CHANGER_EXPANSION_FEATUREENABLE_COMMAND 0x01
#define CHANGER_EXPANSION_PAYOUT_COMMAND 0x02
#define CHANGER_EXPANSION_PAYOUTSTATUS 0x03
#define CHANGER_EXPANSION_PAYOUTVALUEPOLL 0x04
#define CHANGER_EXPANSION_SENDDIAGNOSTICSTATUS_COMMAND 0x05

#define CHANGER_POWERINGUP 0x0100
#define CHANGER_POWERINGDOWN 0x0200
#define CHANGER_OK 0X0300
#define CHANGER_KEYPADSHIFTED 0x0400
#define CHANGER_MANUALFILLPAYOUTACTIVE 0X0510
#define CHANGER_NEWINVENTORYINFORMATIONAVAILABLE 0X0520
#define CHANGER_INHIBITEDBYVMC 0X0600
#define CHANGER_GENERALCHANGERERROR 0X10
#define CHANGER_GENERALCHANGERERROR_NONSPECIFIC 0X00
#define CHANGER_GENERALCHANGERERROR_CHECKSUM1 0X01
#define CHANGER_GENERALCHANGERERROR_CHECKSUM2 0x02
#define CHANGER_GENERALCHANGERERROR_LOWLINEVOLTAGE 0X03
#define CHANGER_DISCRIMINATORMODULEERROR 0X11
#define CHANGER_GENERALCHANGERERROR_FLIGHTDECKOPEN 0x10
#define CHANGER_GENERALCHANGERERROR_ESCROWRETURNSTUCK 0x11
#define CHANGER_GENERALCHANGERERROR_COINJAMINSENSOR 0x30
#define CHANGER_GENERALCHANGERERROR_DISCRIMINATIONSUBSTANDARD 0x41
#define CHANGER_GENERALCHANGERERROR_VALIDATIONSENSORAOUTOFRANGE 0x50
#define CHANGER_GENERALCHANGERERROR_VALIDATIONSENSORBOUTOFRANGE 0x51
#define CHANGER_GENERALCHANGERERROR_VALIDATIONSENSORCOUTOFRANGE 0x52
#define CHANGER_GENERALCHANGERERROR_OPERATINGTEMPERATUREEXCEEDED 0x53
#define CHANGER_GENERALCHANGERERROR_SIZINGOPTICSFAILURE 0x54

#define CHANGER_ACCEPTGATEMODULEERROR 0x12
#define CHANGER_ACCEPTGATEMODULEERROR_NONSPECIFIC 0x00
#define CHANGER_ACCEPTGATEMODULEERROR_COINSTUCK 0x30
#define CHANGER_ACCEPTGATEMODULEERROR_ACCEPTGATEALARMACTIVE 0x31
#define CHANGER_ACCEPTGATEMODULEERROR_ACCEPTGATEOPENBUTNOCOIN 0x40
#define CHANGER_ACCEPTGATEMODULEERROR_POSTGATESENSORCOVEREDBEFOREGATEOPENED 0x50
#define CHANGER_SEPARATORMODULEERROR 0x13
#define CHANGER_SEPARATORMODULEERROR_NONSPECIFIC 0x00
#define CHANGER_SEPARATORMODULEERROR_SORTSENSOR 0x10
#define CHANGER_DISPENSERMODULEERROR 0x14
#define CHANGER_DISPENSERMODULEERROR_NONSPECIFIC 0x00
#define CHANGER_CASSETTETUBEMODULEERROR 0x15
#define CHANGER_CASSETTETUBEMODULEERROR_NONSPECIFIC 0x00
#define CHANGER_CASSETTETUBEMODULEERROR_CASSETTEREMOVED 0x02
#define CHANGER_CASSETTETUBEMODULEERROR_CASHBOXSENSOR 0x03
#define CHANGER_CASSETTETUBEMODULEERROR_SUNLIGHTONTUBESENSOR 0x04

#define CHANGER_STATUS_ESCROWREQUEST 0x01
#define CHANGER_STATUS_CHANGERPAYOUTBUSY 0x02
#define CHANGER_STATUS_NOCREDIT 0x03
#define CHANGER_STATUS_DEFECTIVETUBESENSOR 0x04
#define CHANGER_STATUS_DOUBLEARRIVAL 0x05
#define CHANGER_STATUS_CNANGERUNPLUGGED 0x06
#define CHANGER_STATUS_TUBEJAM 0x07
#define CHANGER_STATUS_ROMCHECKSUMERROR 0x08
#define CHANGER_STATUS_COINROUTINGERROR 0x09
#define CHANGER_STATUS_BUSY 0x0a
#define CHANGER_STATUS_WASRESET 0x0b
#define CHANGER_STATUS_COINJAM 0x0c
#define CHANGER_STATUS_POSSIBLECREDITEDCOINREMOVAL 0x0d


#define MDB_BUFFER_SIZE 36+10 // ((36 + 1)*2)  // section 2.2, +10 for safety

#define MDB_LOG_MAX  MDB_BUFFER_SIZE

#define MDB_IS_COIN(b)   ((((b) & 0xC0u) == 0x40u))
#define MDB_MAX_POLL_LEN 16

#define MDB_MAX_FRAME_LEN 36+10

// structure for storing the coin changer info
typedef struct
{
  uint8_t CoinChangerFeatureLevel;
  uint16_t CountryOrCurrencyCode;
  uint8_t CoinScalingFactor;
  uint8_t DecimalPlaces;
  uint8_t CoinsRouteable[16];
  uint8_t CoinTypeCredit[16];
  uint8_t NumCoinTypes;
} CoinChanger_Info_t;

// struct for storing the tube status
typedef struct
{
  uint16_t Full_Status; // Bits 0-15 indican si el tubo está lleno
  uint8_t Status[16];   // Cantidad de monedas en cada tubo (1-16)
  uint8_t Total_Tubes;  // Cantidad de bytes de datos recibidos (sin checksum)
} Tube_Status_t;

typedef struct
{
  unsigned int SoftwareVersion;
  unsigned char AlternativePayout;
  unsigned char ExtendedDiagnostic;
  unsigned char ControlledManualFillAndPayout;
  unsigned char FTLSupported;
  unsigned char ManufacturerCode[3];
  unsigned char SerialNumber[12];
  unsigned char ModelRevision[12];
} CCID_Data_t;



// extern CoinChanger_Info_t coin_changer_info;



#ifdef	__cplusplus
}
#endif

#endif	/* MDB_H */

