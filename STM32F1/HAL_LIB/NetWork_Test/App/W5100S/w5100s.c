#include "w5100s.h"
#if (_WIZCHIP_ == W5100S)

void WIZCHIP_WRITE(uint32_t AddrSel, uint8_t wb )
{
   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();

#if( (_WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_))
   WIZCHIP.IF.SPI._write_byte(0xF0);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0xFF00) >>  8);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x00FF) >>  0);
   WIZCHIP.IF.SPI._write_byte(wb);    // Data write (write 1byte data)
#elif ( (_WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_BUS_INDIR_) )
   WIZCHIP.IF.BUS._write_data(IDM_AR0,(AddrSel & 0xFF00) >>  8);
   WIZCHIP.IF.BUS._write_data(IDM_AR1,(AddrSel & 0x00FF));  
   WIZCHIP.IF.BUS._write_data(IDM_DR,wb);
#endif
   WIZCHIP.CS._deselect();
   WIZCHIP_CRITICAL_EXIT();
}

uint8_t  WIZCHIP_READ(uint32_t AddrSel)
{
   uint8_t ret;
  
   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();

#if( (_WIZCHIP_IO_MODE_ ==  _WIZCHIP_IO_MODE_SPI_))
   WIZCHIP.IF.SPI._write_byte(0x0F);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0xFF00) >>  8);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x00FF) >>  0);
   ret = WIZCHIP.IF.SPI._read_byte(); 
#elif ( (_WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_BUS_INDIR_) )
   WIZCHIP.IF.BUS._write_data(IDM_AR0,(AddrSel & 0xFF00) >>  8);
   WIZCHIP.IF.BUS._write_data(IDM_AR1,(AddrSel & 0x00FF));
   ret = WIZCHIP.IF.BUS._read_data(IDM_DR);
#endif
   WIZCHIP.CS._deselect();
   WIZCHIP_CRITICAL_EXIT();
   return ret;
}

void WIZCHIP_WRITE_BUF(uint32_t AddrSel, uint8_t* pBuf, uint16_t len)
{
   uint16_t i = 0;

   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();   //M20150601 : Moved here.

#if ((_WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_))

   WIZCHIP.IF.SPI._write_byte(0xF0);
   WIZCHIP.IF.SPI._write_byte((((uint16_t)(AddrSel+i)) & 0xFF00) >>  8);
   WIZCHIP.IF.SPI._write_byte((((uint16_t)(AddrSel+i)) & 0x00FF) >>  0);

   for(i = 0; i < len; i++)
   {
     WIZCHIP.IF.SPI._write_byte(pBuf[i]);    // Data write (write 1byte data)
   }
#elif ( (_WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_BUS_INDIR_) )
   setMR(getMR()|MR_AI);     
   WIZCHIP.IF.BUS._write_data(IDM_AR0,(AddrSel & 0xFF00) >>  8);
   WIZCHIP.IF.BUS._write_data(IDM_AR1,(AddrSel & 0x00FF));
   for(i = 0 ; i < len; i++)
     WIZCHIP.IF.BUS._write_data(IDM_DR,pBuf[i]);
   setMR(getMR() & ~MR_AI);   

   
#endif
   
   WIZCHIP.CS._deselect();  //M20150601 : Moved here.
   WIZCHIP_CRITICAL_EXIT();
}


void WIZCHIP_READ_BUF (uint32_t AddrSel, uint8_t* pBuf, uint16_t len)
{
   uint16_t i = 0;
   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();   //M20150601 : Moved here.
   
#if ( (_WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_) )

   WIZCHIP.IF.SPI._write_byte(0x0F);
   WIZCHIP.IF.SPI._write_byte((uint16_t)((AddrSel+i) & 0xFF00) >>  8);
   WIZCHIP.IF.SPI._write_byte((uint16_t)((AddrSel+i) & 0x00FF) >>  0);

   for(i = 0; i < len; i++)
   {
      pBuf[i] = WIZCHIP.IF.SPI._read_byte(); 
   }
#elif ( (_WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_BUS_INDIR_) )
   setMR(getMR() | MR_AI);
   WIZCHIP.IF.BUS._write_data(IDM_AR0,(AddrSel & 0xFF00) >>  8);
   WIZCHIP.IF.BUS._write_data(IDM_AR1,(AddrSel & 0x00FF));  
   for(i = 0 ; i < len; i++)   
      pBuf[i]  = WIZCHIP.IF.BUS._read_data(IDM_DR);    
   setMR(getMR() & ~MR_AI); 
#endif
   WIZCHIP.CS._deselect();    //M20150601 : Moved Here.
   WIZCHIP_CRITICAL_EXIT();
}

///////////////////////////////////
// Socket N regsiter IO function //
///////////////////////////////////

uint16_t getSn_TX_FSR(uint8_t sn)
{
  uint16_t val=0,val1=0;
  do
  {
    val1 = WIZCHIP_READ(Sn_TX_FSR(sn));
    val1 = (val1 << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_TX_FSR(sn),1));
    if (val1 != 0)
    {
      val = WIZCHIP_READ(Sn_TX_FSR(sn));
      val = (val << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_TX_FSR(sn),1));
    }
  }while (val != val1);
  return val;
}


uint16_t getSn_RX_RSR(uint8_t sn)
{
  uint16_t val=0,val1=0;
  do
  {
    val1 = WIZCHIP_READ(Sn_RX_RSR(sn));
    val1 = (val1 << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_RX_RSR(sn),1));
    if (val1 != 0)
    {
      val = WIZCHIP_READ(Sn_RX_RSR(sn));
      val = (val << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_RX_RSR(sn),1));
    }
  }while (val != val1);
  return val;
}

/////////////////////////////////////
// Sn_TXBUF & Sn_RXBUF IO function //
/////////////////////////////////////
uint32_t getSn_RxBASE(uint8_t sn)
{
   int8_t  i;
#if ( _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_BUS_DIR_)
   uint32_t rxbase = _W5100_IO_BASE_ + _WIZCHIP_IO_RXBUF_;
#else   
   uint32_t rxbase = _WIZCHIP_IO_RXBUF_;
#endif   
   for(i = 0; i < sn; i++)
      rxbase += getSn_RxMAX(i);

   return rxbase;
}

uint32_t getSn_TxBASE(uint8_t sn)
{
   int8_t  i;
#if ( _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_BUS_DIR_)
   uint32_t txbase = _W5100_IO_BASE_ + _WIZCHIP_IO_TXBUF_;
#else   
   uint32_t txbase = _WIZCHIP_IO_TXBUF_;
#endif   
   for(i = 0; i < sn; i++)
      txbase += getSn_TxMAX(i);
   return txbase;
}

/**
@brief  This function is being called by send() and sendto() function also. for copy the data form application buffer to Transmite buffer of the chip.

This function read the Tx write pointer register and after copy the data in buffer update the Tx write pointer
register. User should read upper byte first and lower byte later to get proper value.
And this function is being used for copy the data form application buffer to Transmite
buffer of the chip. It calculate the actual physical address where one has to write
the data in transmite buffer. Here also take care of the condition while it exceed
the Tx memory uper-bound of socket.

*/
void wiz_send_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
  uint16_t ptr;
  uint16_t size;
  uint16_t dst_mask;
  uint16_t dst_ptr;

  ptr = getSn_TX_WR(sn);

  dst_mask = ptr & getSn_TxMASK(sn);
  dst_ptr = getSn_TxBASE(sn) + dst_mask;
  
  if (dst_mask + len > getSn_TxMAX(sn)) 
  {
    size = getSn_TxMAX(sn) - dst_mask;
    WIZCHIP_WRITE_BUF(dst_ptr, wizdata, size);
    wizdata += size;
    size = len - size;
    dst_ptr = getSn_TxBASE(sn);
    WIZCHIP_WRITE_BUF(dst_ptr, wizdata, size);
  } 
  else
  {
    WIZCHIP_WRITE_BUF(dst_ptr, wizdata, len);
  }

  ptr += len;

  setSn_TX_WR(sn, ptr);  
}


/**
@brief  This function is being called by recv() also. This function is being used for copy the data form Receive buffer of the chip to application buffer.

This function read the Rx read pointer register
and after copy the data from receive buffer update the Rx write pointer register.
User should read upper byte first and lower byte later to get proper value.
It calculate the actual physical address where one has to read
the data from Receive buffer. Here also take care of the condition while it exceed
the Rx memory uper-bound of socket.
*/
void wiz_recv_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
  uint16_t ptr;
  uint16_t size;
  uint16_t src_mask;
  uint16_t src_ptr;

  ptr = getSn_RX_RD(sn);
  
  src_mask = (uint32_t)ptr & getSn_RxMASK(sn);
  src_ptr = (getSn_RxBASE(sn) + src_mask);

  
  if( (src_mask + len) > getSn_RxMAX(sn) ) 
  {
    size = getSn_RxMAX(sn) - src_mask;
    WIZCHIP_READ_BUF((uint32_t)src_ptr, (uint8_t*)wizdata, size);
    wizdata += size;
    size = len - size;
  src_ptr = getSn_RxBASE(sn);
    WIZCHIP_READ_BUF(src_ptr, (uint8_t*)wizdata, size);
  } 
  else
  {
    WIZCHIP_READ_BUF(src_ptr, (uint8_t*)wizdata, len);
  }
    
  ptr += len;
  
  setSn_RX_RD(sn, ptr);
}

void wiz_recv_ignore(uint8_t sn, uint16_t len)
{
  uint16_t ptr;

  ptr = getSn_RX_RD(sn);
  
  ptr += len;
  setSn_RX_RD(sn,ptr);
}

//todo comment needed
void wiz_mdio_write(uint8_t PHYMDIO_regadr, uint16_t var)
{
  //set the address to write
  setPHYRR(PHYMDIO_regadr);
  //set the data to write
  setPHYDIR(var);
  //write command
  setPHYACR(PHYACR_WRITE);

  while(getPHYACR() != 0){
    //wait until command executed.
  }
}

uint16_t wiz_mdio_read(uint8_t PHYMDIO_regadr)
{
  setPHYRR(PHYMDIO_regadr);
  setPHYACR(PHYACR_READ);
  while(getPHYACR() != 0){
    //wait until command executed.
  }
  return getPHYDOR();
}

#endif
