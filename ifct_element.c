//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};

typedef struct ifs_ele {
	int index; //number
	int age; //age
	int time; //time
	place_t place[N_HISTORY]; //place[N_HISTORY]
} ifs_ele_t;

//���� static ifs_ele_t ifsarray[20];
//���� static in ifs_cnt; 

void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	int i;
	
	ifs_ele_t* ptr;
	
	ptr = (ifs_ele_t*)malloc(sizeof(ifs_ele_t));
	
	ptr->index = index;
	ptr->age = age;
	ptr->time = detected_time;
		
	for(i=0;i<5;i++)
	{
		ptr->place[N_HISTORY] = history_place[i];  
	}
		
	return ptr;
	//���� ifsarray[ifs_cnt]. index = index;
	//���� ifsarray[ifs_cnt]. age = age;
    //���� ifs_cnt++; 
	//���� return &ifsarray[ifs_cnt-1]; 
}

int ifctele_getAge(void* obj)
{
	ifs_ele_t* ptr = (ifs_ele_t*)obj;
	return ptr->age;
}


int ifctele_getHistPlaceIndex(void* obj, int index)
{
	ifs_ele_t* ptr = (ifs_ele_t*)obj;
	return ptr->place;   
}

unsigned int ifctele_getinfestedTime(void* obj)
{
	ifs_ele_t* ptr = (ifs_ele_t*)obj;
	return ptr->time;
}

void ifctele_printElement(void* obj)
{
	
	ifs_ele_t* ptr = (ifs_ele_t*)obj; 
	
	printf("Index : %i\n", ptr->index); 
	printf("Age : %i\n", ptr->age);
	printf("Time : %i\n", ptr->time);  
	
	int i;
	
	for (i=0;i<5;i++)
	{
		printf("Track : %s\n", ifctele_getPlaceName(ptr->place)); 
	}
}



char* ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}
