//////////////////////////////////////////////////////////
// SpeedMod Neutral
//////////////////////////////////////////////////////////
#define CT00CM	0x0064	//MCM 0x0064=10000k 5B=9100K 43=6700K 3A=5500K

#define CTHIGHVAL1		0x0138,0x8383, //CBCB
#define CTHIGHVAL2		0x013C,0x8383, //CBCB
#define CTHIGHVAL3		0x0140,0x8383, //CBCR
#define CTHIGHVAL4		0x0144,0x8383, //CRCR
#define CTHIGHVAL5		0x0148,0x8383, //CRCR

#define CTHIGHVAL1C		0x0138,0x8888, //CBCB
#define CTHIGHVAL2C		0x013C,0x8888, //CBCB
#define CTHIGHVAL3C		0x0140,0x887E, //CBCR
#define CTHIGHVAL4C		0x0144,0x7E7E, //CRCR
#define CTHIGHVAL5C		0x0148,0x7E7E, //CRCR

#define CTHIGHVAL1W		0x0138,0x7E7E, //CBCB
#define CTHIGHVAL2W		0x013C,0x7E7E, //CBCB
#define CTHIGHVAL3W		0x0140,0x7E88, //CBCR
#define CTHIGHVAL4W		0x0144,0x8888, //CRCR
#define CTHIGHVAL5W		0x0148,0x8888, //CRCR

mDNIe_data_type mDNIe_Video[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //de 127, ce off //de 63
	0x00ac,0x0080, //skin detect off, cs 512 //cs 128
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1
	CTHIGHVAL2
	CTHIGHVAL3
	CTHIGHVAL4
	CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Camera[]= 
{
	0x0084,0x0020, //20, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 0, ce off
	0x00ac,0x0000, //skin detect off, cs off
	0x00b4,0x0100, //3ff, //de th.
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1
	CTHIGHVAL2
	CTHIGHVAL3
	CTHIGHVAL4
	CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Camera_Outdoor_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + ove
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 0, ce off
	0x00ac,0x0000, //skin detect off, cs off
	0x00b4,0x0100, //3ff, //de th.
	0x0100,0x5040, //ove
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1
	CTHIGHVAL2
	CTHIGHVAL3
	CTHIGHVAL4
	CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_UI[]= 
{
	0x0084,0x0020, //20, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //0x01f0 de 15, ce off //0x00f0 de 7, ce off //0x0010 de 0, ce off //de off, ce off
	0x00ac,0x0010, //20, //skin detect off, cs 32
	0x00b4,0x0100, //de th.
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1
	CTHIGHVAL2
	CTHIGHVAL3
	CTHIGHVAL4
	CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Video_Warm[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off //de 63
	0x00ac,0x0080, //200, //skin detect off, cs 512 cs 128
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1W
	CTHIGHVAL2W
	CTHIGHVAL3W
	CTHIGHVAL4W
	CTHIGHVAL5W
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Video_WO_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1W
	CTHIGHVAL2W
	CTHIGHVAL3W
	CTHIGHVAL4W
	CTHIGHVAL5W
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Video_Cold[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1C
	CTHIGHVAL2C
	CTHIGHVAL3C
	CTHIGHVAL4C
	CTHIGHVAL5C
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Video_CO_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1C
	CTHIGHVAL2C
	CTHIGHVAL3C
	CTHIGHVAL4C
	CTHIGHVAL5C
	END_SEQ, 0x0000,

};

mDNIe_data_type mDNIe_Outdoor_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + ove
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 127, ce off //de 63
	0x00ac,0x0010, //skin detect off, cs 512 //cs 256
	0x00b4,0x0100, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	CTHIGHVAL1
	CTHIGHVAL2
	CTHIGHVAL3
	CTHIGHVAL4
	CTHIGHVAL5	
	END_SEQ, 0x0000,

};
#if 0 //Disable for SpeedMod Gingerbread kernel for now
//////////////////////////////////////////////////////////
// SpeedMod COLD
//////////////////////////////////////////////////////////
#define COLD_CTHIGHVAL1		0x0138,0x8F8F, //CBCB +15
#define COLD_CTHIGHVAL2		0x013C,0x8F8F, //CBCB
#define COLD_CTHIGHVAL3		0x0140,0x8F79, //CBCR -7
#define COLD_CTHIGHVAL4		0x0144,0x7979, //CRCR
#define COLD_CTHIGHVAL5		0x0148,0x7979, //CRCR

#define COLD_CTHIGHVAL1C		0x0138,0x9494, //CBCB
#define COLD_CTHIGHVAL2C		0x013C,0x9494, //CBCB
#define COLD_CTHIGHVAL3C		0x0140,0x9474, //CBCR
#define COLD_CTHIGHVAL4C		0x0144,0x7474, //CRCR
#define COLD_CTHIGHVAL5C		0x0148,0x7474, //CRCR

#define COLD_CTHIGHVAL1W		0x0138,0x8A8A, //CBCB
#define COLD_CTHIGHVAL2W		0x013C,0x8A8A, //CBCB
#define COLD_CTHIGHVAL3W		0x0140,0x8A7E, //CBCR
#define COLD_CTHIGHVAL4W		0x0144,0x7E7E, //CRCR
#define COLD_CTHIGHVAL5W		0x0148,0x7E7E, //CRCR

mDNIe_data_type COLD_mDNIe_Video[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //de 127, ce off //de 63
	0x00ac,0x0080, //skin detect off, cs 512 //cs 128
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1
	COLD_CTHIGHVAL2
	COLD_CTHIGHVAL3
	COLD_CTHIGHVAL4
	COLD_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type COLD_mDNIe_Camera[]= 
{
	0x0084,0x0020, //20, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 0, ce off
	0x00ac,0x0000, //skin detect off, cs off
	0x00b4,0x0100, //3ff, //de th.
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1
	COLD_CTHIGHVAL2
	COLD_CTHIGHVAL3
	COLD_CTHIGHVAL4
	COLD_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type COLD_mDNIe_Camera_Outdoor_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + ove
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 0, ce off
	0x00ac,0x0000, //skin detect off, cs off
	0x00b4,0x0100, //3ff, //de th.
	0x0100,0x5040, //ove
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1
	COLD_CTHIGHVAL2
	COLD_CTHIGHVAL3
	COLD_CTHIGHVAL4
	COLD_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type COLD_mDNIe_UI[]= 
{
	0x0084,0x0020, //20, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //0x01f0 de 15, ce off //0x00f0 de 7, ce off //0x0010 de 0, ce off //de off, ce off
	0x00ac,0x0010, //20, //skin detect off, cs 32
	0x00b4,0x0100, //de th.
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1
	COLD_CTHIGHVAL2
	COLD_CTHIGHVAL3
	COLD_CTHIGHVAL4
	COLD_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type COLD_mDNIe_Video_Warm[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off //de 63
	0x00ac,0x0080, //200, //skin detect off, cs 512 cs 128
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1W
	COLD_CTHIGHVAL2W
	COLD_CTHIGHVAL3W
	COLD_CTHIGHVAL4W
	COLD_CTHIGHVAL5W
	END_SEQ, 0x0000,
};

mDNIe_data_type COLD_mDNIe_Video_WO_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1W
	COLD_CTHIGHVAL2W
	COLD_CTHIGHVAL3W
	COLD_CTHIGHVAL4W
	COLD_CTHIGHVAL5W
	END_SEQ, 0x0000,
};

mDNIe_data_type COLD_mDNIe_Video_Cold[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1C
	COLD_CTHIGHVAL2C
	COLD_CTHIGHVAL3C
	COLD_CTHIGHVAL4C
	COLD_CTHIGHVAL5C
	END_SEQ, 0x0000,
};

mDNIe_data_type COLD_mDNIe_Video_CO_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1C
	COLD_CTHIGHVAL2C
	COLD_CTHIGHVAL3C
	COLD_CTHIGHVAL4C
	COLD_CTHIGHVAL5C
	END_SEQ, 0x0000,

};

mDNIe_data_type COLD_mDNIe_Outdoor_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + ove
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 127, ce off //de 63
	0x00ac,0x0010, //skin detect off, cs 512 //cs 256
	0x00b4,0x0100, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	COLD_CTHIGHVAL1
	COLD_CTHIGHVAL2
	COLD_CTHIGHVAL3
	COLD_CTHIGHVAL4
	COLD_CTHIGHVAL5	
	END_SEQ, 0x0000,

};

//////////////////////////////////////////////////////////
// SpeedMod WARM
//////////////////////////////////////////////////////////
#define WARM_CTHIGHVAL1		0x0138,0x7D7D, //CBCB -3
#define WARM_CTHIGHVAL2		0x013C,0x7D7D, //CBCB
#define WARM_CTHIGHVAL3		0x0140,0x7D84, //CBCR +4
#define WARM_CTHIGHVAL4		0x0144,0x8484, //CRCR
#define WARM_CTHIGHVAL5		0x0148,0x8484, //CRCR

#define WARM_CTHIGHVAL1C		0x0138,0x8282, //CBCB
#define WARM_CTHIGHVAL2C		0x013C,0x8282, //CBCB
#define WARM_CTHIGHVAL3C		0x0140,0x827F, //CBCR
#define WARM_CTHIGHVAL4C		0x0144,0x7F7F, //CRCR
#define WARM_CTHIGHVAL5C		0x0148,0x7F7F, //CRCR

#define WARM_CTHIGHVAL1W		0x0138,0x7878, //CBCB
#define WARM_CTHIGHVAL2W		0x013C,0x7878, //CBCB
#define WARM_CTHIGHVAL3W		0x0140,0x7889, //CBCR
#define WARM_CTHIGHVAL4W		0x0144,0x8989, //CRCR
#define WARM_CTHIGHVAL5W		0x0148,0x8989, //CRCR

mDNIe_data_type WARM_mDNIe_Video[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //de 127, ce off //de 63
	0x00ac,0x0080, //skin detect off, cs 512 //cs 128
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1
	WARM_CTHIGHVAL2
	WARM_CTHIGHVAL3
	WARM_CTHIGHVAL4
	WARM_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type WARM_mDNIe_Camera[]= 
{
	0x0084,0x0020, //20, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 0, ce off
	0x00ac,0x0000, //skin detect off, cs off
	0x00b4,0x0100, //3ff, //de th.
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1
	WARM_CTHIGHVAL2
	WARM_CTHIGHVAL3
	WARM_CTHIGHVAL4
	WARM_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type WARM_mDNIe_Camera_Outdoor_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + ove
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 0, ce off
	0x00ac,0x0000, //skin detect off, cs off
	0x00b4,0x0100, //3ff, //de th.
	0x0100,0x5040, //ove
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1
	WARM_CTHIGHVAL2
	WARM_CTHIGHVAL3
	WARM_CTHIGHVAL4
	WARM_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type WARM_mDNIe_UI[]= 
{
	0x0084,0x0020, //20, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //0x01f0 de 15, ce off //0x00f0 de 7, ce off //0x0010 de 0, ce off //de off, ce off
	0x00ac,0x0010, //20, //skin detect off, cs 32
	0x00b4,0x0100, //de th.
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1
	WARM_CTHIGHVAL2
	WARM_CTHIGHVAL3
	WARM_CTHIGHVAL4
	WARM_CTHIGHVAL5
	END_SEQ, 0x0000,
};

mDNIe_data_type WARM_mDNIe_Video_Warm[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off //de 63
	0x00ac,0x0080, //200, //skin detect off, cs 512 cs 128
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1W
	WARM_CTHIGHVAL2W
	WARM_CTHIGHVAL3W
	WARM_CTHIGHVAL4W
	WARM_CTHIGHVAL5W
	END_SEQ, 0x0000,
};

mDNIe_data_type WARM_mDNIe_Video_WO_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1W
	WARM_CTHIGHVAL2W
	WARM_CTHIGHVAL3W
	WARM_CTHIGHVAL4W
	WARM_CTHIGHVAL5W
	END_SEQ, 0x0000,
};

mDNIe_data_type WARM_mDNIe_Video_Cold[]= 
{
	0x0084,0x0020, //60, //algorithm selection+pcc + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1C
	WARM_CTHIGHVAL2C
	WARM_CTHIGHVAL3C
	WARM_CTHIGHVAL4C
	WARM_CTHIGHVAL5C
	END_SEQ, 0x0000,
};

mDNIe_data_type WARM_mDNIe_Video_CO_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x07f1, //ff1, //de 127, ce off
	0x00ac,0x0080, //200, //skin detect off, cs 512
	0x00b4,0x0100, //001, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1C
	WARM_CTHIGHVAL2C
	WARM_CTHIGHVAL3C
	WARM_CTHIGHVAL4C
	WARM_CTHIGHVAL5C
	END_SEQ, 0x0000,

};

mDNIe_data_type WARM_mDNIe_Outdoor_Mode[]= 
{
	0x0084,0x00a0, //a0, //algorithm selection + ove
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0011, //de 127, ce off //de 63
	0x00ac,0x0010, //skin detect off, cs 512 //cs 256
	0x00b4,0x0100, //de th.
	0x0100,0x5050, //ove
	0x0120,CT00CM, //MCM 10000K
	WARM_CTHIGHVAL1
	WARM_CTHIGHVAL2
	WARM_CTHIGHVAL3
	WARM_CTHIGHVAL4
	WARM_CTHIGHVAL5	
	END_SEQ, 0x0000,

};
#endif //End of disable for SpeedMod Gingerbread
#if defined(CONFIG_ARIES_LATONA)

mDNIe_data_type mDNIe_Gallery[]= 
{
	0x0084,0x0020, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x0ff0, //de 127, ce off
	0x00ac,0x0200, //skin detect off, cs 512
	0x00b4,0x0100, //de th.
	0x0120,0x0064, //MCM 10000K
	0x0140,0x8d00, //cb
	0x0148,0x0073, //cr
	0x0134,0xFFF8, //LSF 248
	END_SEQ,0x0000,
};

#endif
#if 0 //Original
//#else   ///////////////////////////////////////////////////////////////

mDNIe_data_type mDNIe_Video[]= 
{
	0x0084, 0x0040,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005c,
	0x009C, 0x0ff0,
	0x00AC, 0x00E0, 
	0x00B4, 0x0001, 
	0x00C0, 0x0400,
	0x00C4, 0x7200, 
	0x00C8, 0x008d, 
	0x00D0, 0x0100, 
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Camera[]= 
{
	0x0084, 0x0040,
	0x0090, 0x0000,
	0x0094, 0x0FFF,
	0x0098, 0x005C,
	0x009C, 0x0010,
	0x00AC, 0x0000,
	0x00B4, 0x03FF,
	0x00C0, 0x0400,
	0x00C4, 0x7200,
	0x00C8, 0x008D,
	0x00D0, 0x00C0,
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Camera_Outdoor_Mode[]= 
{
	0x0084, 0x0090,
	0x0090, 0x0000,
	0x0094, 0x0FFF,
	0x0098, 0x005C,
	0x009C, 0x0010,
	0x00AC, 0x0000,
	0x00B4, 0x03FF,
	0x0100, 0x6050,
	0x0198, 0x0001,
	0x0194, 0x0011,
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_UI[]= 
{
//#if 0
	0x0084, 0x0000,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005c,
	0x009C, 0x0010,
	0x00AC, 0x0000,
	0x00B4, 0x03ff,
	END_SEQ, 0x0000,
//original
	0x0084, 0x0040,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005C,
	0x009C, 0x0ff0, //0x0ff0
	0x00AC, 0x0080, //0x0080
	0x00B4, 0x0180, //0x0180
	0x00C0, 0x0400,
	0x00C4, 0x7200,
	0x00C8, 0x008D,
	0x00D0, 0x00C0,
	0x0100, 0x0000,
	END_SEQ, 0x0000,
//#else
	0x0084,0x0020, //algorithm selection + mcm
	0x0090,0x0000, //decontour th.
	0x0094,0x0fff, //directional th.
	0x0098,0x005c, //simplicity th.
	0x009c,0x00f0, //0x01f0 de 15, ce off //0x00f0 de 7, ce off //0x0010 de 0, ce off 
	0x00ac,0x0020, //skin detect off, cs 32
	0x00b4,0x0100, //de th.
	0x0120,0x0064, //MCM 10000K
	0x0140,0x8000, //cb VC 0x9300=+19, C 0x8d00=+13, N 0x8000=0, W 0x7300=-13
	0x0148,0x0080, //cr VC 0x006d=-19, C 0x0073=-13, N 0x0080=0, W 0x008d=+13
	0x0134,0xFFF8, //LSF 248
	END_SEQ, 0x0000,
//#endif	
};

mDNIe_data_type mDNIe_Video_Warm[]= 
{
	0x0084, 0x0020,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005C,
	0x009C, 0x0FF0,
	0x00AC, 0x0000,
	0x00B4, 0x0001,
	0x0120, 0x0028,
	0x0138, 0x7600,
	0x0140, 0x0090,
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Video_WO_Mode[]= 
{
	0x0084, 0x0090,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005C,
	0x009C, 0x0ff0,
	0x00AC, 0x0000,
	0x00B4, 0x0001,
	0x0100, 0x6050,
	0x0198, 0x0001,
	0x0194, 0x0011,
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Video_Cold[]= 
{
	0x0084, 0x0020,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005c,
	0x009C, 0x0ff0,
	0x00AC, 0x0000,
	0x00B4, 0x0001,
	0x0120, 0x0064,
	0x0140, 0x9400,
	0x0148, 0x006D,
	END_SEQ, 0x0000,
};

mDNIe_data_type mDNIe_Video_CO_Mode[]= 
{
	0x0084, 0x0090,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005C,
	0x009C, 0x0ff0,
	0x00AC, 0x0000,
	0x00B4, 0x0001,
	0x0100, 0x6050,
	0x0198, 0x0001,
	0x0194, 0x0011,
	END_SEQ, 0x0000,

};

mDNIe_data_type mDNIe_Outdoor_Mode[]= 
{
	0x0084, 0x0090,
	0x0090, 0x0000,
	0x0094, 0x0fff,
	0x0098, 0x005C,
	0x009C, 0x0ff0,
	0x00AC, 0x0000,
	0x00B4, 0x0001,
	0x0100, 0x6050,
	0x0198, 0x0001,
	0x0194, 0x0011,
	END_SEQ, 0x0000,

};

#endif
