#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//	A chip-8 emulator,written by Mouzakitis Nikolaos,Crete,2017.
//			CHIP-8 emulator.


//===================================.
//Keaboard implementation.   	0-a ||
//				1-s ||
//				2-d ||
//				3-f ||
//				4-g ||
//				5-h ||
//				6-j ||
//				7-k ||
//				8-l ||
//				9-z ||
//				A-x ||
//				B-c ||
//				C-v ||
//				D-b ||
//				E-n ||
//				F-m ||
//==================================**
//==================================**

int run_state = 1;

struct syst
{
	uint8_t V[16];			//	16 registers.
	uint16_t index_register;
	uint16_t opcode;		//	current opcode.
	uint16_t pc;			//	program counter.
	uint16_t stack[16];
	uint8_t stack_pointer;
	uint8_t screen[64*32];
	uint8_t delay_timer;
	uint8_t sound_timer;
	uint8_t Wmem;			//	written mem.(how many bytes after 0x200 have instructions)
	unsigned char memory[4096];
	uint8_t kb[16]; 		//	keabord 16 keys.
} chip;

void system_initialization(struct syst *s)
{
	s->memory[0] = 0xf0;	//zero sprite
	s->memory[1] = 0x90;
	s->memory[2] = 0x90;
	s->memory[3] = 0x90;
	s->memory[4] = 0xf0;
	s->memory[5] = 0x20;	//one sprite
	s->memory[6] = 0x60;
	s->memory[7] = 0x20;
	s->memory[8] = 0x20;
	s->memory[9] = 0x70;
	s->memory[10] = 0xf0;	//two sprite
	s->memory[11] = 0x10;
	s->memory[12] = 0xf0;
	s->memory[13] = 0x80;
	s->memory[14] = 0xf0;
	s->memory[15] = 0xf0;	//three sprite
	s->memory[16] = 0x10;
	s->memory[17] = 0xf0;
	s->memory[18] = 0x10;
	s->memory[19] = 0xf0;
	s->memory[20] = 0x90;	//four sprite
	s->memory[21] = 0x90;
	s->memory[22] = 0xf0;
	s->memory[23] = 0x10;
	s->memory[24] = 0x10;
	s->memory[25] = 0xf0;	//five sprite
	s->memory[26] = 0x80;
	s->memory[27] = 0xf0;
	s->memory[28] = 0x10;
	s->memory[29] = 0xf0;
	s->memory[30] = 0xf0;	//six sprite
	s->memory[31] = 0x80;
	s->memory[32] = 0xf0;
	s->memory[33] = 0x90;
	s->memory[34] = 0xf0;
	s->memory[35] = 0xf0;	//seven sprite
	s->memory[36] = 0x10;
	s->memory[37] = 0x20;
	s->memory[38] = 0x40;
	s->memory[39] = 0x40;
	s->memory[40] = 0xf0;	//eight sprite
	s->memory[41] = 0x90;
	s->memory[42] = 0xf0;
	s->memory[43] = 0x90;
	s->memory[44] = 0xf0;
	s->memory[45] = 0xf0;	//nine sprite
	s->memory[46] = 0x90;
	s->memory[47] = 0xf0;
	s->memory[48] = 0x10;
	s->memory[49] = 0xf0;
	s->memory[50] = 0xf0;	//a sprite
	s->memory[51] = 0x90;
	s->memory[52] = 0xf0;
	s->memory[53] = 0x90;
	s->memory[54] = 0x90;
	s->memory[55] = 0xe0;	//b sprite
	s->memory[56] = 0x90;
	s->memory[57] = 0xe0;
	s->memory[58] = 0x90;
	s->memory[59] = 0xe0;
	s->memory[60] = 0xf0;	//c sprite
	s->memory[61] = 0x80;
	s->memory[62] = 0x80;
	s->memory[63] = 0x80;
	s->memory[64] = 0xf0;
	s->memory[65] = 0xe0;	//d sprite
	s->memory[66] = 0x90;
	s->memory[67] = 0x90;
	s->memory[68] = 0x90;
	s->memory[69] = 0xe0;
	s->memory[70] = 0xf0;	//e sprite
	s->memory[71] = 0x80;
	s->memory[72] = 0xf0;
	s->memory[73] = 0x80;
	s->memory[74] = 0xf0;
	s->memory[75] = 0xf0;	//f sprite
	s->memory[76] = 0x80;
	s->memory[77] = 0xf0;
	s->memory[78] = 0x80;
	s->memory[79] = 0X80;
//	printf("[sprites]:Initialized.............->OK\n");
	int i;

	for(i = 512; i < 4096; i++)
		s->memory[i] = 0;
	
	s->delay_timer = 0;
	s->sound_timer = 0;
	s->stack_pointer = -1;
	s->index_register = 0;
	s->opcode = 0;
	s->pc = 0x200;

	for(i = 0; i < 16; i++)
	{
		s->kb[i] = 0;
		s->stack[i] = 0;
	}
//	printf("[Stack]:Initialized................>OK\n");
//	printf("[Keaboard]:Initialized.............>OK\n");
	for(i = 0; i < 16; i++)
		s->V[i] = 0;
//	printf("[registers]:Initialized............>OK\n");
}

void load_on_memory(unsigned char *buffer,unsigned char *memory,int fsize)
{
	int i,j;
	
	for(i = 0,j=512; i < fsize; i++)	// in memory we do not store the spaces or new lince characters.
		if( (buffer[i] != ' ') && (buffer[i] != '\n') )		
			memory[j++] = buffer[i];
	chip.Wmem = j;		//saving value in Wmem.
}

void keaboard_update(void)
{
	char key;
	
	if(key = kbhit())
	{
		switch(key)
		{
			case 'a': 
				chip.kb[0] = 1;
				break;
			case 's':
				chip.kb[1] = 1;
				break;
			case 'd': 
				chip.kb[2] = 1;
				break;
			case 'f':
				chip.kb[3] = 1;
				break;
			case 'g': 
				chip.kb[4] = 1;
				break;
			case 'h':
				chip.kb[5] = 1;
				break;
			case 'j': 
				chip.kb[6] = 1;
				break;
			case 'k':
				chip.kb[7] = 1;
				break;
			case 'l': 
				chip.kb[8] = 1;
				break;
			case 'z':
				chip.kb[9] = 1;
				break;
			case 'x': 
				chip.kb[10] = 1;
				break;
			case 'c':
				chip.kb[11] = 1;
				break;
			case 'v': 
				chip.kb[12] = 1;
				break;
			case 'b':
				chip.kb[13] = 1;
				break;
			case 'n': 
				chip.kb[14] = 1;
				break;
			case 'm':
				chip.kb[15] = 1;
				break;
			default: 
				;
		}
	}
}

void print_MEM(struct syst *s)
{	//used it for debbuging to check what is written actually on memory after 512 index.
	int i;
	printf("written memory inspect.\n");
	for(i = 0; i <chip.Wmem; i++)
		printf("%c",chip.memory[512+i]);
}
void clear_DISPLAY(void)
{
	int i;

	for(i = 0; i < 32*64; i++)
		chip.screen[i] = 0;
}

void kb_init(void)
{
	int i;
	
	for(i = 0; i < 16; i++)
		chip.kb[i] = 0;

}
int hex_to_dec(char ch)
{
	switch(ch)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a': 
		case 'A': return 10;
		case 'b': 
		case 'B': return 11;
		case 'c':
		case 'C': return 12;
		case 'd': 
		case 'D': return 13;
		case 'e': 
		case 'E': return 14;
		case 'f': 
		case 'F': return 15;
		default : printf("no hexadecimal encryption\n");
			  return -1;
	}
}

void operate()
{
	char ch,buffer[4];
	int h1,h2,h3,j,reg_no,value = 0,t = 0;
	int normal_execution = 1;	// if true the program counter increments by 4 bytes to next instruction.
	int switcher;			// used for carry's borrow's cause 8bit int's wont hold them on overflow.
	
	for(j = 0; j < 4; j++)
	{
		buffer[j] = chip.memory[chip.pc+t];
		printf("%c",buffer[j]);
		t++;
	}
	putchar('\n');

	switch(buffer[0])
	{
		case 'b':	//COSMAC_VIP instruction [BMMM : jump to MMM + V0]
		case 'B':
				h1 = hex_to_dec(buffer[1]);
				h2 = hex_to_dec(buffer[2]);
				h3 = hex_to_dec(buffer[3]);
				
				normal_execution = 0;
				
				chip.pc = 16*16*h1 + 16*h2 + h3 + chip.V[0];
				
				break;
	

		case '0':	//COSMAC_VIP instruction 00e0 clearing display.
				if(!strncmp(buffer,"00e0",4) || (!strncmp(buffer,"00E0",4)))	
				{
					printf("Instr. clear_display\n");
					clear_DISPLAY();
					break;
				}
				else if( !strncmp(buffer,"00EE",4) || (!strncmp(buffer,"00ee",4) ) )
				//COSMAC_VIP instruction [00EE :return from subroutine : RET]
					normal_execution = 0;
					chip.pc = chip.stack[chip.stack_pointer];
					chip.stack_pointer -=1;					
					break;
		
		case '2':	//COSMAC_VIP instruction [2MMM : call subroutine at MMM : CALL addr]
				chip.stack_pointer += 1;
				chip.stack[chip.stack_pointer] = chip.pc;
				normal_execution = 0;
				h1 = hex_to_dec(buffer[1]);
				h2 = hex_to_dec(buffer[2]);
				h3 = hex_to_dec(buffer[3]);
				chip.pc = 16*16*h1+16*h2+h3;
				break;
		case '3':	//COSMAC_VIP instruction [3XKK : skip next instr. if VX == KK]
				
				h1 = hex_to_dec(buffer[1]);
				h2 = hex_to_dec(buffer[2]);
				h3 = hex_to_dec(buffer[3]);
				value = 16*h2 + h3;

				if(chip.V[h1] == value)
					chip.pc += 4;			

				break;
		case '4':	//COSMAC_VIP instruction [4XKK : skip next instr. if VX != KK]
				
				h1 = hex_to_dec(buffer[1]);
				h2 = hex_to_dec(buffer[2]);
				h3 = hex_to_dec(buffer[3]);
				value = 16*h2 + h3;

				if(chip.V[h1] != value)
					chip.pc += 4;			

				break;
		
		case '5':	//COSMAC_VIP instruction [5XY0 : Skip next inst. if VX == VY]
				
				h1 = hex_to_dec(buffer[1]);
				h2 = hex_to_dec(buffer[2]);
				
				if(chip.V[h1] == chip.V[h2])
					chip.pc += 4;	
				
				break;
		case '9':	//COSMAC_VIP instruction.[9XY0 : Skip next instr. if VX != VY]
				
				h1 = hex_to_dec(buffer[1]);
				h2 = hex_to_dec(buffer[2]);
				
				if(chip.V[h1] != chip.V[h2])
					chip.pc += 4;

				break;

		case '6':	//COSMAC_VIP instruction 6XKK : VX = KK		
				printf("instr. 6xkk\n");
				reg_no = hex_to_dec(buffer[1]);
				h1 = 16*hex_to_dec(buffer[2]);
				h2 = 1 *hex_to_dec(buffer[3]);
				value = h1 + h2;
				chip.V[reg_no] = value;
				break;
		

		case '8':	
				if(buffer[3] =='0') //COSMAV_VIP instruction [8XY0 :  VX = VY]	
				{
					printf("instr. 8xy0\n");
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					chip.V[h1] = chip.V[h2];
					break;
				}
				else if(buffer[3]=='1') //COSMAC_VIP instruction [8XY1: VX = VX | VY]
				{
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					chip.V[h1] = chip.V[h1] | chip.V[h2];
					break;				
				}
				else if(buffer[3] == '2') //COSMAC_VIP instruction [8XY2 : VX = VX & VY]
				{
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					chip.V[h1] = chip.V[h1] & chip.V[h2];
					break;
				}
				else if(buffer[3] == '3') //COSMAC_VIP instruction [8XY2 : VX = VX ^ VY]
				{
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					chip.V[h1] = chip.V[h1] ^ chip.V[h2];
					break;
				}
				
				else if(buffer[3]=='4') //COSMAC_VIP [8XY4: VX = VX + VY(if VX + VY <=ff VF = 00,else 01]
				{
					printf("instr.8xy4\n");
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					value =16* hex_to_dec('f')+hex_to_dec('f'); //255
					switcher = chip.V[h1] + chip.V[h2] ;
					chip.V[h1] += chip.V[h2];
				
					if(switcher <= 255)
						chip.V[15] = 0;
					else if(switcher > 255)
						chip.V[15] = 1;
				
					break;
				}
				else if(buffer[3]=='5') //COSMAC_VIP[ 8XY5: VX = VX - VY(if Vx-Vy<0,VF=0,else 01]
				{
					printf("instr 8xy5\n");
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					value = 255; //FF
					switcher = chip.V[h1] - chip.V[h2] ;
					chip.V[h1] -= chip.V[h2];
					
					if(switcher < 0 )
						chip.V[15] = 0;
					else
						chip.V[15] = 1;
					break;
				}
				else if(buffer[3] == '6') //COSMAC_VIP SHR Vx{,Vy}
				{
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					
					if(chip.V[h1] % 2) //least-significant is 1
						chip.V[15] = 1;
					else
						chip.V[15] = 0;
					
					chip.V[h1] /= 2;
					break;
				}		
				else if(buffer[3] == '7')//COSMAC_VIP instr.[8xy7 : SUBN VX VY]
				{
					h1 = hex_to_dec(buffer[1]);
					h2 = hex_to_dec(buffer[2]);
					switcher = chip.V[h2] - chip.V[h1];
					chip.V[h1] = chip.V[h2] - chip.V[h1];
					
					if(switcher < 0)
						chip.V[15] = 0;
					else 
						chip.V[15] = 1;
					break;
				}	
				else if( (buffer[3] == 'E') || (buffer[3] == 'e') ) // [8xyE : SHL Vx {,Vy} ]
				{
					h1 = hex_to_dec(buffer[1]);
					switcher = chip.V[h1] & (0x80);	// if m.s.b is 1 ,switcher = 0x80	
					
					if(switcher == (0x80))
						chip.V[15] = 1;
					else
						chip.V[15] = 0;
					
					chip.V[h1] *= 2;
					break;

				}		
		case '7':	//COSMAC_VIP instruction 7XKK : [VX = VX + KK.]
				printf("instr: 7xkk\n");
				ch = buffer[1];
				reg_no = hex_to_dec(ch);
				h1 = 16*hex_to_dec(buffer[2]);
				h2 = 1*hex_to_dec(buffer[3]);
				value = h1+h2;
				chip.V[reg_no] += value;
				break;

		case '1':	// instruction Created for debbuging, 1111-->run_state = 0 & exit.
				if(!strncmp(buffer,"1111",4))
				{	
					run_state = 0;
					printf("HALT instruction.[debug-only].\n");
					break;
				}
				//COSMAC_VIP instruction 1MMM : Go to MMM
				else	
				{
					chip.pc =1* hex_to_dec(buffer[3]) + 16*hex_to_dec(buffer[2]) + 16*16*hex_to_dec(buffer[1]) ;			  
					normal_execution = 0;
					break;
				}
		default:
				printf("Uknown instruction.-->exiting\n");
				run_state = 0;
				break;
	}

	if(normal_execution)
		chip.pc += 4;		//incrementing program counter to show the next instruction.
	
}
int main(int argc,char *argv[])
{
	FILE *rom;
		
	system_initialization(&chip);
	
	printf("program starts at: %x(hex)\n",chip.pc);
	
	rom = fopen("fisher.ch8","rb");
	
	if(rom == NULL)
	{
		printf("Error occured\n");
		exit(1);
	}
	
	fseek(rom,0L,SEEK_END);
	int fsize = ftell(rom);
	
	fseek(rom,0L,SEEK_SET);
	
	unsigned char *buffer = malloc(fsize);
	
	fread(buffer,fsize,1,rom);
	fclose(rom);
	load_on_memory(buffer,chip.memory,fsize);
	
	while(run_state)
	{
		keaboard_update();
		printf("program_counter: %d\n",chip.pc);
		operate();
		delay(450);
		kb_init();
	}
	printf("v[12] %d  v[15]: %d\n",chip.V[12],chip.V[15]);
	return 0;
}
