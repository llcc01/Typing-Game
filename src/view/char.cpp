#include "view/char.hpp"

namespace view
{

const uint8_t charMap[53][CHAR_SIZE * CHAR_SIZE / 16] = {


{0x00,0x00,0x04,0x00,0x80,0x07,0x00,0xF0,0x03,0x00,0xFE,0x00,0xC0,0xCF,0x00,0xC0,0xC1,0x00,0xC0,0xC1,0x00,0xC0,0xCF,0x00,0x00,0xFE,0x00,0x00,0xF0,0x03,0x00,0x80,0x07,0x00,0x00,0x04},/*"A",0*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x18,0x06,0x40,0x18,0x06,0x40,0x18,0x06,0x40,0x18,0x06,0xC0,0x3F,0x03,0x80,0xF7,0x03,0x00,0xE0,0x01,0x00,0x00,0x00},/*"B",1*/
{0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0xFF,0x01,0x80,0x83,0x03,0xC0,0x00,0x06,0x40,0x00,0x06,0x60,0x00,0x06,0x60,0x00,0x04,0x40,0x00,0x06,0x40,0x00,0x06,0xC0,0x00,0x06,0x00,0x00,0x00},/*"C",2*/
{0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x00,0x06,0x40,0x00,0x06,0x40,0x00,0x06,0x40,0x00,0x06,0xC0,0x00,0x02,0xC0,0x01,0x03,0x80,0xFF,0x01,0x00,0xFF,0x00,0x00,0x00,0x00},/*"D",3*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x18,0x06,0x40,0x18,0x06,0x40,0x18,0x06,0x40,0x18,0x06,0x40,0x18,0x06,0x40,0x18,0x06,0x00,0x00,0x00,0x00,0x00,0x00},/*"E",4*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x18,0x00,0x40,0x18,0x00,0x40,0x18,0x00,0x40,0x18,0x00,0x40,0x18,0x00,0x40,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"F",5*/
{0x00,0x00,0x00,0x00,0xFE,0x00,0x80,0xFF,0x03,0xC0,0x01,0x03,0xC0,0x00,0x06,0x40,0x00,0x06,0x60,0x10,0x04,0x60,0x10,0x04,0x60,0x10,0x06,0x40,0xF0,0x07,0xC0,0xF0,0x07,0x00,0x00,0x00},/*"G",6*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x06,0x40,0x00,0x06,0x40,0x00,0x06,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x00,0x06,0x40,0x00,0x06,0x40,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00},/*"I",7*/
{0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x00,0x00,0x00},/*"H",8*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x06,0x40,0x00,0x06,0x40,0x00,0x06,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x00,0x06,0x40,0x00,0x06,0x40,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00},/*"I",9*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x00,0x38,0x00,0x00,0x7C,0x00,0x00,0xE7,0x00,0x80,0xC3,0x01,0xC0,0x00,0x07,0x40,0x00,0x06,0x00,0x00,0x04,0x00,0x00,0x00},/*"K",10*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x00},/*"L",11*/
{0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0x1F,0x00,0xC0,0x03,0x00,0x00,0x1F,0x00,0x00,0x78,0x00,0x00,0x78,0x00,0x00,0x0F,0x00,0xC0,0x03,0x00,0xC0,0x1F,0x00,0xC0,0xFF,0x07,0x00,0x00,0x04},/*"M",12*/
{0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0xC0,0x01,0x00,0x80,0x07,0x00,0x00,0x1E,0x00,0x00,0x78,0x00,0x00,0xE0,0x01,0x00,0x80,0x07,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x00,0x00,0x00},/*"N",13*/
{0x00,0x00,0x00,0x00,0xFF,0x01,0x80,0xFF,0x03,0xC0,0x00,0x07,0x40,0x00,0x06,0x60,0x00,0x04,0x60,0x00,0x04,0x40,0x00,0x06,0xC0,0x00,0x07,0x80,0xEF,0x03,0x00,0xFF,0x01,0x00,0x00,0x00},/*"O",14*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x20,0x00,0x40,0x20,0x00,0x40,0x20,0x00,0x40,0x30,0x00,0xC0,0x38,0x00,0x80,0x1F,0x00,0x00,0x0F,0x00,0x00,0x00,0x00},/*"P",15*/
{0x00,0x00,0x00,0x00,0xFF,0x01,0x80,0xFF,0x03,0xC0,0x00,0x07,0x40,0x00,0x06,0x60,0x00,0x1C,0x60,0x00,0x3C,0x40,0x00,0x26,0xC0,0x00,0x67,0xC0,0xEF,0x63,0x00,0xFF,0x21,0x00,0x00,0x20},/*"Q",16*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x10,0x00,0x40,0x10,0x00,0x40,0x38,0x00,0xC0,0xF8,0x00,0xC0,0xCF,0x03,0x80,0x87,0x07,0x00,0x00,0x06,0x00,0x00,0x00},/*"R",17*/
{0x00,0x00,0x00,0x00,0x03,0x06,0x80,0x07,0x06,0xC0,0x0C,0x06,0x40,0x18,0x04,0x60,0x18,0x04,0x60,0x18,0x04,0x60,0x30,0x06,0x40,0x70,0x07,0x40,0xE0,0x03,0x00,0xC0,0x01,0x00,0x00,0x00},/*"S",18*/
{0x00,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0xC0,0xFF,0x07,0xC0,0xFF,0x07,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00},/*"T",19*/
{0x00,0x00,0x00,0xC0,0xFF,0x01,0xC0,0xFF,0x03,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x06,0x00,0x00,0x06,0xC0,0xFF,0x03,0xC0,0xFF,0x01,0x00,0x00,0x00},/*"U",20*/
{0x40,0x00,0x00,0xC0,0x03,0x00,0xC0,0x1F,0x00,0x00,0xFE,0x00,0x00,0xF0,0x03,0x00,0x80,0x07,0x00,0x00,0x07,0x00,0xE0,0x03,0x00,0xFC,0x00,0x80,0x1F,0x00,0xC0,0x03,0x00,0x40,0x00,0x00},/*"V",21*/
{0x00,0x00,0x00,0xC0,0xFF,0x07,0x00,0xFE,0x07,0x00,0x00,0x07,0x00,0xE0,0x01,0x00,0x3C,0x00,0x00,0x3C,0x00,0x00,0xF0,0x01,0x00,0x80,0x07,0x00,0xE0,0x07,0xC0,0xFF,0x07,0x40,0x00,0x00},/*"W",22*/
{0x00,0x00,0x00,0x40,0x00,0x06,0xC0,0x01,0x07,0x80,0xC3,0x03,0x00,0xEF,0x00,0x00,0x3C,0x00,0x00,0x3C,0x00,0x00,0xEF,0x00,0x80,0xC3,0x03,0xC0,0x01,0x07,0x40,0x00,0x06,0x00,0x00,0x04},/*"X",23*/
{0x00,0x00,0x00,0xC0,0x00,0x00,0xC0,0x03,0x00,0x00,0x0F,0x00,0x00,0x1E,0x00,0x00,0xF8,0x07,0x00,0xF0,0x07,0x00,0x1C,0x00,0x00,0x0F,0x00,0xC0,0x03,0x00,0xC0,0x00,0x00,0x40,0x00,0x00},/*"Y",24*/
{0x00,0x00,0x00,0x40,0x00,0x06,0x40,0x00,0x07,0x40,0xC0,0x07,0x40,0xE0,0x06,0x40,0x78,0x06,0x40,0x1C,0x06,0x40,0x0E,0x06,0xC0,0x03,0x06,0xC0,0x01,0x06,0x40,0x00,0x06,0x00,0x00,0x00},/*"Z",25*/
{0x00,0x00,0x00,0x00,0x00,0x01,0x00,0xC6,0x07,0x00,0xE2,0x06,0x00,0x62,0x04,0x00,0x22,0x04,0x00,0x22,0x06,0x00,0x22,0x02,0x00,0xFE,0x03,0x00,0xFC,0x07,0x00,0x00,0x00,0x00,0x00,0x00},/*"a",26*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0x07,0xE0,0xFF,0x07,0x00,0x06,0x04,0x00,0x02,0x04,0x00,0x02,0x04,0x00,0x02,0x06,0x00,0x06,0x03,0x00,0xFE,0x03,0x00,0xF8,0x00,0x00,0x00,0x00},/*"b",27*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x01,0x00,0xFC,0x03,0x00,0x06,0x06,0x00,0x02,0x06,0x00,0x02,0x04,0x00,0x02,0x04,0x00,0x02,0x06,0x00,0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00},/*"c",28*/
{0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0xFC,0x03,0x00,0x0E,0x07,0x00,0x06,0x04,0x00,0x02,0x04,0x00,0x02,0x06,0x00,0x02,0x03,0xE0,0xFF,0x01,0xE0,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00},/*"d",29*/
{0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0xFC,0x03,0x00,0x2E,0x07,0x00,0x22,0x06,0x00,0x22,0x04,0x00,0x22,0x04,0x00,0x22,0x04,0x00,0x26,0x04,0x00,0x3C,0x06,0x00,0x38,0x00,0x00,0x00,0x00},/*"e",30*/
{0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x0C,0x00,0x00,0x0C,0x00,0x80,0xFF,0x07,0xE0,0xFF,0x07,0x60,0x0C,0x00,0x30,0x0C,0x00,0x30,0x0C,0x00,0x30,0x0C,0x00,0x20,0x0C,0x00,0x00,0x00,0x00},/*"f",31*/
{0x00,0x00,0x00,0x00,0x00,0x39,0x00,0xFC,0x7F,0x00,0x7E,0x66,0x00,0x42,0x46,0x00,0xC2,0x46,0x00,0xC2,0x46,0x00,0x42,0x46,0x00,0x7E,0x66,0x00,0x3E,0x7C,0x00,0x02,0x3C,0x00,0x00,0x00},/*"g",32*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x04,0x00,0x02,0x04,0x00,0x02,0x04,0x70,0xFE,0x07,0x70,0xFE,0x07,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x00},/*"i",33*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0x07,0xE0,0xFF,0x07,0x00,0x06,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x0E,0x00,0x00,0xFE,0x07,0x00,0x00,0x00,0x00,0x00,0x00},/*"h",34*/
{0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x02,0x40,0x00,0x02,0x40,0x00,0x02,0x40,0x00,0x02,0x40,0x20,0x02,0x60,0x70,0xFE,0x3F,0x60,0xFE,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"j",35*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0x07,0xE0,0xFF,0x07,0x00,0x20,0x00,0x00,0x70,0x00,0x00,0xD8,0x00,0x00,0x8C,0x03,0x00,0x06,0x07,0x00,0x02,0x06,0x00,0x00,0x04,0x00,0x00,0x00},/*"k",36*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x04,0x20,0x00,0x04,0x20,0x00,0x04,0xE0,0xFF,0x07,0xE0,0xFF,0x07,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x00},/*"l",37*/
{0x00,0x00,0x00,0x00,0xFE,0x07,0x00,0xF8,0x07,0x00,0x06,0x00,0x00,0x02,0x00,0x00,0xFE,0x07,0x00,0xFC,0x07,0x00,0x06,0x00,0x00,0x02,0x00,0x00,0xFE,0x07,0x00,0xFE,0x07,0x00,0x00,0x00},/*"m",38*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x07,0x00,0xFC,0x07,0x00,0x06,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x0E,0x00,0x00,0xFE,0x07,0x00,0x00,0x00,0x00,0x00,0x00},/*"n",39*/
{0x00,0x00,0x00,0x00,0xF8,0x01,0x00,0xFC,0x03,0x00,0x06,0x07,0x00,0x02,0x06,0x00,0x02,0x04,0x00,0x02,0x04,0x00,0x02,0x06,0x00,0x06,0x07,0x00,0xFC,0x03,0x00,0xF8,0x01,0x00,0x00,0x00},/*"o",40*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x7F,0x00,0xFC,0x7F,0x00,0x06,0x04,0x00,0x02,0x04,0x00,0x02,0x04,0x00,0x02,0x06,0x00,0x06,0x03,0x00,0xFE,0x03,0x00,0xF8,0x00,0x00,0x00,0x00},/*"p",41*/
{0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0xFC,0x03,0x00,0x0E,0x07,0x00,0x06,0x06,0x00,0x02,0x04,0x00,0x02,0x06,0x00,0x02,0x03,0x00,0xFE,0x7D,0x00,0xFE,0x7F,0x00,0x00,0x00,0x00,0x00,0x00},/*"q",42*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x07,0x00,0xFE,0x07,0x00,0x0C,0x00,0x00,0x06,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x1E,0x00,0x00,0x1C,0x00,0x00,0x00,0x00},/*"r",43*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x06,0x00,0x3E,0x06,0x00,0x32,0x04,0x00,0x62,0x04,0x00,0x62,0x04,0x00,0x62,0x06,0x00,0xC2,0x07,0x00,0xC2,0x03,0x00,0x00,0x00,0x00,0x00,0x00},/*"s",44*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0xC0,0xFF,0x03,0xE0,0xFF,0x07,0x00,0x02,0x06,0x00,0x02,0x04,0x00,0x02,0x04,0x00,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00},/*"t",45*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x03,0x00,0xFE,0x07,0x00,0x00,0x06,0x00,0x00,0x04,0x00,0x00,0x06,0x00,0x00,0x02,0x00,0x00,0x01,0x00,0xFE,0x07,0x00,0x00,0x00,0x00,0x00,0x00},/*"u",46*/
{0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x1E,0x00,0x00,0xFC,0x00,0x00,0xE0,0x03,0x00,0x00,0x07,0x00,0x00,0x07,0x00,0xE0,0x03,0x00,0xF8,0x00,0x00,0x1E,0x00,0x00,0x06,0x00,0x00,0x00,0x00},/*"v",47*/
{0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0xF8,0x07,0x00,0x00,0x06,0x00,0xC0,0x03,0x00,0x78,0x00,0x00,0x78,0x00,0x00,0xE0,0x03,0x00,0x00,0x07,0x00,0xF0,0x07,0x00,0xFE,0x01,0x00,0x02,0x00},/*"w",48*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x06,0x06,0x00,0x0E,0x07,0x00,0xDC,0x01,0x00,0xF0,0x00,0x00,0xF0,0x00,0x00,0xF8,0x01,0x00,0x8E,0x03,0x00,0x06,0x06,0x00,0x02,0x04,0x00,0x00,0x00},/*"x",49*/
{0x00,0x00,0x00,0x00,0x06,0x40,0x00,0x1E,0x40,0x00,0x7C,0x60,0x00,0xE0,0x33,0x00,0x80,0x3F,0x00,0x00,0x0F,0x00,0xE0,0x03,0x00,0xF8,0x00,0x00,0x1E,0x00,0x00,0x06,0x00,0x00,0x00,0x00},/*"y",50*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x06,0x00,0x02,0x07,0x00,0xC2,0x07,0x00,0xE2,0x06,0x00,0x72,0x06,0x00,0x1A,0x06,0x00,0x0E,0x06,0x00,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00},/*"z",51*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x0C,0x00,0x80,0x04,0x00,0x80,0x03,0x00,0x60,0x1F,0x00,0xE0,0x1F,0x00,0x80,0x03,0x00,0x80,0x04,0x00,0xC0,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"*",52*/



};

} // namespace view

