//halt
void io_hlt(void);
void io_cli(void);

void io_out8(int port,int data);

int io_load_eflags(void);

void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start,int end,unsigned char *rgb);
void boxfill8(unsigned char *vram,int xsize,unsigned char c,int x0,int y0,int x1,int y1);

//define boundary
#define X_SIZE 
#define Y_SIZE

#define COL8_00000
#define COL8_FF001
#define COL8_00FF2
#define COL8_FFFF3
#define COL8_00004
#define COL8_FF005
#define COL8_00FF6
#define COL8_FFFF7
#define COL8_C6C68
#define COL8_84009
#define COL8_008410
#define COL8_848411
#define COL8_000012
#define COL8_840013
#define COL8_008414
#define COL8_848415

void HariMain(void)
{
	//video ram
	char *vram;
	int xsize,ysize;

	init_palette();
	vram = (char *) 0xa0000;
	xsize = X_SIZE;
	ysize = Y_SIZE;
	//cube
	boxfill8(vram, xsize, COL8_008484,0,0,xsize-1,ysize-29);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 28, xsize -  1, ysize - 28);
	boxfill8(vram, xsize, COL8_FFFFFF,  0,         ysize - 27, xsize -  1, ysize - 27);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 26, xsize -  1, ysize -  1);
	boxfill8(vram, xsize, COL8_FFFFFF,  3,         ysize - 24, 59,         ysize - 24);
	boxfill8(vram, xsize, COL8_FFFFFF,  2,         ysize - 24,  2,         ysize -  4);
	boxfill8(vram, xsize, COL8_848484,  3,         ysize -  4, 59,         ysize -  4);
	boxfill8(vram, xsize, COL8_848484, 59,         ysize - 23, 59,         ysize -  5);
	boxfill8(vram, xsize, COL8_000000,  2,         ysize -  3, 59,         ysize -  3);
	boxfill8(vram, xsize, COL8_000000, 60,         ysize - 24, 60,         ysize -  3);
	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

	for (;;) {
	io_hlt();
}
}

void init_palette(void)
{
	//color
	static unsigned char table_rgb[16*3] = {
		0x00, 0x00, 0x00,
		0xff, 0x00, 0x00,
		0x00, 0xff, 0x00
		0xff, 0xff, 0x00,
		0x00, 0x00, 0xff,
		0xff, 0x00, 0xff,
		0x00, 0xff, 0xff,
		0xff, 0xff, 0xff,
		0xc6, 0xc6, 0xc6,
		0x84, 0x00, 0x00,
		0x00, 0x84, 0x00,
		0x84, 0x84, 0x00,
		0x00, 0x00, 0x84,
		0x84, 0x00, 0x84,
		0x00, 0x84, 0x84,
		0x84, 0x84, 0x84
	};
	//
	set_palette(0, 15, table_rgb);
	return;

}

void set_palette(int start, int end, unsigned char *rgb )
{
	int i,eflags;
	eflags = io_load_eflags();
	io_cli();
	io_out8(0x03c8,start);
	for (i = start; i <= end; i++){
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);
	return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x,y;
	for	(y = y0;y<=y1;y++) {
		for (x = x0; x <= x1; x++)
			vram[y*xsize + x] = c;
	}
	return;
}
