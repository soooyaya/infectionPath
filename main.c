//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2

int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int place;
    int cnt;
    int placeHist[N_HISTORY];
    int i;
    int minAge, maxAge;
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1], "r");
    if (fp == NULL) //에러 핸들링 코드 (제대로 못 열었다) 
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    //#if 
    //1-2. loading each patient informations
    while (3 == fscanf(fp, "%i %i %i", &pIndex, &age, &time))
    {
    	for(i=0;i<5;i++)
		{
		  fscanf(fp, "%i", &placeHist[i]);  //수정 fscanf(5개 읽기); 
		}
			
		ifct_element = ifctele_genElement(pIndex, age, time, placeHist);
		
		ifctdb_addTail(ifct_element);
		
		//지움 printf(%i번째 환자 감염 경로 : ", 환자번호); 
	}
	//#endif
    
    //1-3. FILE pointer close
    fclose(fp);
    
    /*
    {
    	int place1, place2;
    	
		place1 = 3;
    	place2 = 15;
    	
    	printf("The first place is %s\n", ifctele_getPlaceName(place1)) ;
    	printf("The second place is %s\n", ifctele_getPlaceName(place2)) ;
	}
    */
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
                //지움 printf("age : %i\n", ifctele_getAge(ifct_element));   
                printf("Patient index : ");
                scanf("%i", &pIndex);
                ifct_element = ifctdb_getData(pIndex); 
                ifctele_printElement(ifct_element); 
                
                int place1, place2, place3, place4, place5;  //최근 5개 이동 장소 출력 

    	        /*
				printf("The first place is %s\n", ifctele_getPlaceName(place1));
    	        printf("The second place is %s\n", ifctele_getPlaceName(place2)); 
    	        printf("The third place is %s\n", ifctele_getPlaceName(place3)); 
    	        printf("The fourth place is %s\n", ifctele_getPlaceName(place4)); 
    	        printf("The fifth place is %s\n", ifctele_getPlaceName(place5)); 
	            */
				                
                break;
                

            case MENU_PLACE:
            	printf("Place Name : ");
            	scanf("%s", &placeHist[N_HISTORY]);
            	
            	for(i=0;i<5;i++) 
            	{
            		ifct_element = ifctdb_getData(i); 
            		//!!이어서 풀어라!!
            		cnt++;
				}
                
                printf("There are %i patients detected in %s.\n", cnt, place);
            
    	        
                break;
                
                
            case MENU_AGE:
            	printf("minimal age : ");
            	scanf("%i", &minAge);
            	
            	printf("maximal age : ");
            	scanf("%i", &maxAge);
            	
            	for (i=0;i<5;i++)
            	{
            		ifct_element = ifctdb_getData(i); 
            		if(minAge <= ifctele_getAge(ifctdb_getData(i)) && ifctele_getAge(ifctdb_getData(i)) <= maxAge)
            		  printf("There are %i patients detected in %s.\n", cnt, place);
				}
                
                break;
                
            case MENU_TRACK:
            	printf("Patient index : ");
            	scanf("%i", &pIndex);
            	
            
            	/*
				현재환자=입력값;
				while (현재환자가 누군가 있음)
				{
					전파자 = trackInfester(현재환자);
					if (전파자가 있으면)
					   printf("Patient %i is infected with patient %i. \n", 현재환자, 전파자);
					else
					   최초전파자 = 현재환자;
					   현재환자 = 전파자;
					   
			    for (i번째 환자)
			    {
			    	만난시간=isMet(현재환자, i번째 환자);
					if (만난시간>0) //만났다면
					{
						if (지금까지 환자 중 만난시간이 가장 이른가?)
						{
							전파자 = i; 
						}
					 } 
				}
				
				return 전파자;
				
			    
				for (i=2;i<N_HISTORY;i++)
				{
					현재환자의 i번째 이동장소 시점 계산;
					계산된 시점에서의 대상환자 이동장소 계산;
					if (i번째 이동장소 == 대상환자 이동장소)
					{
						만난시간 = i번째 이동장소 시점; 
					 } 
			    }	 
	
			    }
				
			   
			    int convertTimeToIndex(int time, int infestedTime)
			    {
			    int index = -1;
				
				if (time <= infestedTime && time > infestedTime-N_HISTORY)
				{
				    index = N_HISTORY-(infestedTime - time)-1;
				}
				
				return index;
		        }
		       */

		    
            	printf("Patient %i is infected with Patient %i.\n", pIndex);
            	
        
                break;
                
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
