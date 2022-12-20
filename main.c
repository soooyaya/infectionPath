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
    if (fp == NULL) //���� �ڵ鸵 �ڵ� (����� �� ������) 
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
		  fscanf(fp, "%i", &placeHist[i]);  //���� fscanf(5�� �б�); 
		}
			
		ifct_element = ifctele_genElement(pIndex, age, time, placeHist);
		
		ifctdb_addTail(ifct_element);
		
		//���� printf(%i��° ȯ�� ���� ��� : ", ȯ�ڹ�ȣ); 
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
                //���� printf("age : %i\n", ifctele_getAge(ifct_element));   
                printf("Patient index : ");
                scanf("%i", &pIndex);
                ifct_element = ifctdb_getData(pIndex); 
                ifctele_printElement(ifct_element); 
                
                int place1, place2, place3, place4, place5;  //�ֱ� 5�� �̵� ��� ��� 

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
            		//!!�̾ Ǯ���!!
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
				����ȯ��=�Է°�;
				while (����ȯ�ڰ� ������ ����)
				{
					������ = trackInfester(����ȯ��);
					if (�����ڰ� ������)
					   printf("Patient %i is infected with patient %i. \n", ����ȯ��, ������);
					else
					   ���������� = ����ȯ��;
					   ����ȯ�� = ������;
					   
			    for (i��° ȯ��)
			    {
			    	�����ð�=isMet(����ȯ��, i��° ȯ��);
					if (�����ð�>0) //�����ٸ�
					{
						if (���ݱ��� ȯ�� �� �����ð��� ���� �̸���?)
						{
							������ = i; 
						}
					 } 
				}
				
				return ������;
				
			    
				for (i=2;i<N_HISTORY;i++)
				{
					����ȯ���� i��° �̵���� ���� ���;
					���� ���������� ���ȯ�� �̵���� ���;
					if (i��° �̵���� == ���ȯ�� �̵����)
					{
						�����ð� = i��° �̵���� ����; 
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
