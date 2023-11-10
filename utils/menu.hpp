#ifndef UTILS_MENU_HPP
#define UTILS_MENU_HPP
#define byte win_byte_override

#include <iostream>
#include <conio.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// Fungsi untuk mengarahkan kursor ke koordinat (x,y)
void gotoXY(int x, int y) { 
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition); 
}

// Fungsi untuk membuat border dengan karakter unicode
void frame(int width1, int width2, int height1, int height2, int utfwidth1 = 223, int utfwidth2 = 220, int utfheight1 = 219, int utfheight2 = 219){
	for (int i = width1;  i <= width2;i-=-1){
		// this_thread::sleep_for(chrono::milliseconds(1));
		gotoXY(i,height1);std::cout << char(utfwidth1) << std::endl;
		gotoXY(i,height2);std::cout << char(utfwidth2) << std::endl;
	}
	for (int i = height1;  i <= height2;i-=-1){
		gotoXY(width1,i);std::cout << char(utfheight1) << std::endl;
		gotoXY(width2,i);std::cout << char(utfheight2) << std::endl;
	}
}

// Fungsi untuk membuat garis horizontal
void lineX(int start, int finish, int y, int unicode){
	for(int i = start; i <= finish; i-=-1){
		gotoXY(i,y);std::cout << char(unicode) << std::endl;
	}
}

// Fungsi untuk membuat garis vertikal
void lineY(int start, int finish, int x, int unicode){
	for(int i = start; i <= finish; i-=-1){
		gotoXY(x,i);std::cout << char(unicode) << std::endl;
	}
}

// Fungsi untuk membuat frame utama
void frameMain(){
	// Mozaik atas
	for(int i = 4; i < 8;i-=-2){
		lineX(25,145,i,206);
		lineX(25,145,i+1,232);
	}
	// Mozaik bawah
	for(int i = 23; i < 27;i-=-2){
		lineX(25,145,i,232);
		lineX(25,145,i+1,206);
	}
	// Mozaik kiri
	for(int i = 25; i < 35;i-=-2){
		lineY(8,22,i,206);
		lineY(8,22,i+1,232);
	}
	// Mozaik kanan
	for(int i = 135; i < 145;i-=-2){
		lineY(8,22,i,206);
		lineY(8,22,i+1,232);
	}
	// Frame luar
	frame(25,145,3,27,220,223);
	// Frame dalam
	frame(35,135,8,22);
}

// Fungsi untuk membuat frame menu awal
void frameAwal(){
	system("cls");
	system("color 70");
	frameMain();
	frame(58,112,10,12); // menu awal
	frame(48,68,17,19); // login
	frame(75,95,17,19); // lihat barang
	frame(102,122,17,19); // keluar
}

void blink(std::string text,int x = 57){
	system("cls");
	frame(10,114,3,27,220,223);
	frame(48,78,11,17);
	lineX(11,47,14,178);
	lineX(79,113,14,178);
	gotoXY(x,14);std::cout << text;
	gotoXY(43,26);std::cout << " >> TEKAN APA SAJA UNTUK MELANJUTKAN  << " << std::endl;
	getch();
}

#endif