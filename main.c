#include <stdio.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>





int movie(void)
{
    printf("\twhich movie you want to see?\n");
	printf("\t----------------------------\n\n");
	
	MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
	
	/* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if(mysql_query(conn,"Select movie_name,bhasha,movie_veiwing_type from movies;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    

    int i=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    printf("       %d - %s (%s-%s)\n",i+1,row[0],row[1],row[2]);
    i++;
   
    }
	
	mysql_close(conn);
	int n;
	


    printf("\nEnter Choice: ");
	scanf("%d",&n);
	
	return n;
}
void generate_ticket(int movie_choice,int mall,int city,int time,char loginid[30],int seat_nos){
	
	int k;
	char mall_name[30],movie_id[30],showtime[10],cus_name[20],movie_name[20],price[5],screen_no[5];
	printf("\t               Waiting for confirmation");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	  printf("\t              Generating ticket");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	        
	printf("\t          YAY!! Your Booking has been confirmed!\n\n");


	
	// customer name
	MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char buff[1024] = {};
	    char query_stringg[] = {"select cus_name from login where login_id='%s'"};
	    
	    sprintf(buff, query_stringg,loginid);
	    
	    if (mysql_query(conn,buff)) {
	    fprintf(stderr, "%s\n", mysql_error(conn));
	    exit(1);
	}
    res=mysql_use_result(conn);
    row= mysql_fetch_row(res);
    strcpy(cus_name,row[0]);
    mysql_close(conn);
  
	
	
	// first booking or not
    conn = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if(mysql_query(conn,"Show tables;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    int count=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],loginid)==0) { 
    count++;
    }
    mysql_close(conn);


    if (count==0) {
    	
    	
    	// CREATING TABLE!
    	conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
    	
    	
    	char buf3[1024] = {};
	    char query_string3[] = {"create table %s (ticket_id int PRIMARY KEY, movieid varchar(20), mall_name varchar(40), time varchar(20), seats int);"};
	    
	    sprintf(buf3, query_string3,loginid);
	    
	    if (mysql_query(conn,buf3)) {
	    fprintf(stderr, "%s\n", mysql_error(conn));
	    exit(1);
	    }
	    mysql_close(conn);
	    
	    
	    // INSERTING INTO USER TABLE
	    
	    //ticket id=1;
	    
	    conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    if(mysql_query(conn,"Select movie_id from movies;"))
    	{	
        	fprintf(stderr, "%s\n", mysql_error(conn));
        	exit(1);
    	}
    	res=mysql_use_result(conn);
		int i;	
    	for (i=0; i<movie_choice; i++){
    		row=mysql_fetch_row(res);
	        	}
	    strcpy(movie_id,row[0]);
	    
	    mysql_close(conn);
	    
	    
	    //movie name
	    conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buff4[1024] = {};
		    char query_stringg4[] = {"select movie_name from movies where movie_id='%s'"};
		    
		    sprintf(buff4, query_stringg4,movie_id);
		    
		    if (mysql_query(conn,buff4)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
    	res=mysql_use_result(conn);
	    row= mysql_fetch_row(res);
	    strcpy(movie_name,row[0]);
	    mysql_close(conn);
	    
	    
	    // screen number
	    conn = mysql_init(NULL);
	    /* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buff2[1024] = {};
		    char query_stringg2[] = {"select screen_no from movies where movie_id='%s'"};
		    
		    sprintf(buff2, query_stringg2,movie_id);
		    
		    if (mysql_query(conn,buff2)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
	    res=mysql_use_result(conn);
	    row= mysql_fetch_row(res);
	    strcpy(screen_no,row[0]);
	    mysql_close(conn);
	    
	    // ticket price
	    conn = mysql_init(NULL);
	    /* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buff3[1024] = {};
		    char query_stringg3[] = {"select seat_price from price where movie_id='%s'"};
		    
		    sprintf(buff3, query_stringg3,movie_id);
		    
		    if (mysql_query(conn,buff3)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
	    res=mysql_use_result(conn);
	    row= mysql_fetch_row(res);
	    strcpy(price,row[0]);
	    mysql_close(conn);
	    
	    
	    
	    switch (city){
	    	case 1: //nagpur
	    	switch (mall){
	    		case 1: strcpy(mall_name,"VR Mall, Nagpur"); break;
	    		case 2: strcpy(mall_name,"Eternity Mall, Nagpur"); break;
	    		case 3: strcpy(mall_name,"Empress Mall, Nagpur"); break;
			}
			break;
			case 2: //Mumbai
			switch(mall){
				case 1: strcpy(mall_name,"R-City Mall, Mumbai"); break;
	    		case 2: strcpy(mall_name,"Inorbit Mall, Mumbai"); break;
	    		case 3: strcpy(mall_name,"Phoenix Mall, Mumbai"); break;
			}
			break;
	    	case 3: //Delhi
	    	switch(mall){
				case 1: strcpy(mall_name,"Ambience Mall, Delhi"); break;
	    		case 2: strcpy(mall_name,"DLF Mall, Delhi"); break;
	    		case 3: strcpy(mall_name,"Select city walk Mall, Delhi"); break;
			}
			break;
			case 4: //Bangalore
			switch(mall){
				case 1: strcpy(mall_name,"Central Mall, Bangalore"); break;
	    		case 2: strcpy(mall_name,"Orion Mall, Bangalore"); break;
	    		case 3: strcpy(mall_name,"Phoenix market city, Bangalore"); break;
			}
			break;
		}
		
		switch(time){
			case 1: strcpy(showtime,"9-AM"); break;
			case 2: strcpy(showtime,"2-PM"); break;
			case 3: strcpy(showtime,"6-PM"); break;
		}
		
		//seat_nos
		
		
		
		// inserting
		conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
    	
    	
    	char buf2[1024] = {};
	    char query_string2[] = {"insert into %s values (1, '%s', '%s', '%s', %d);"};
	    
	    sprintf(buf2, query_string2,loginid,movie_id,mall_name,showtime,seat_nos);
	    
	    if (mysql_query(conn,buf2)) {
	    fprintf(stderr, "%s\n", mysql_error(conn));
	    exit(1);
	    }
	    mysql_close(conn);
	    
	    
	    // printing ticket
        printf("\t-----------------THEATER BOOKING TICKET----------------\n");
        printf("\t============================================================\n");
        printf("\t Booking ID : 1\t\t\tShow Name : %s\n",movie_name);
        printf("\t Customer  : %s\n",cus_name);
        printf("\t                                           Time      : %s\n",showtime);
        printf("\t                                           Screen    : %s\n",screen_no);
        printf("\t                                           seat No.  : %d  \n",seat_nos);
        printf("\t                                           price . : %s  \n\n",price);
        printf("\t============================================================\n");

    }
    	
    	
	
	else if (count==1){
		
		//ticket id
		conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buf3[1024] = {};
		    char query_string3[] = {"select ticket_id from %s;"};
		    
		    sprintf(buf3, query_string3,loginid);
		    
		    if (mysql_query(conn,buf3)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
	    res=mysql_use_result(conn);
	    int ticket_id=0;
	    while ((row= mysql_fetch_row(res)) != NULL){ 
		ticket_id++ ;}
		ticket_id++;
		mysql_close(conn);
		
		// making ticket id unique
		conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char bufff3[1024] = {};
		    char query_stringgg3[] = {"select ticket_id from %s;"};
		    
		    sprintf(bufff3, query_stringgg3,loginid);
		    
		    if (mysql_query(conn,bufff3)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
	    res=mysql_use_result(conn);
	    int l;
	    for (l=1; l<ticket_id; l++){
	    	row= mysql_fetch_row(res);
		}
		char ticket_id_stringed[1024] = {};
		    char query[] = {"%d"};
		    
		    sprintf(ticket_id_stringed, query,ticket_id);
		    
		if (strcmp(ticket_id_stringed,row[0])==0){
			ticket_id++;
		}
		mysql_close(conn);
		
		conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    if(mysql_query(conn,"Select movie_id from movies;"))
    	{	
        	fprintf(stderr, "%s\n", mysql_error(conn));
        	exit(1);
    	}
    	res=mysql_use_result(conn);
		int i;	
    	for (i=0; i<movie_choice; i++){
    		row=mysql_fetch_row(res);
	        	}
	    strcpy(movie_id,row[0]);
	    
	    mysql_close(conn);
	    
	    
	    //movie name
	    conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buff4[1024] = {};
		    char query_stringg4[] = {"select movie_name from movies where movie_id='%s'"};
		    
		    sprintf(buff4, query_stringg4,movie_id);
		    
		    if (mysql_query(conn,buff4)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
    	res=mysql_use_result(conn);
	    row= mysql_fetch_row(res);
	    strcpy(movie_name,row[0]);
	    mysql_close(conn);
	    
	    
	    // screen number
	    conn = mysql_init(NULL);
	    /* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buff2[1024] = {};
		    char query_stringg2[] = {"select screen_no from movies where movie_id='%s'"};
		    
		    sprintf(buff2, query_stringg2,movie_id);
		    
		    if (mysql_query(conn,buff2)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
	    res=mysql_use_result(conn);
	    row= mysql_fetch_row(res);
	    strcpy(screen_no,row[0]);
	    mysql_close(conn);
	    
	    // ticket price
	    conn = mysql_init(NULL);
	    /* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buff3[1024] = {};
		    char query_stringg3[] = {"select seat_price from price where movie_id='%s'"};
		    
		    sprintf(buff3, query_stringg3,movie_id);
		    
		    if (mysql_query(conn,buff3)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
	    res=mysql_use_result(conn);
	    row= mysql_fetch_row(res);
	    strcpy(price,row[0]);
	    mysql_close(conn);
	    
	    
	    
	    switch (city){
	    	case 1: //nagpur
	    	switch (mall){
	    		case 1: strcpy(mall_name,"VR Mall, Nagpur"); break;
	    		case 2: strcpy(mall_name,"Eternity Mall, Nagpur"); break;
	    		case 3: strcpy(mall_name,"Empress Mall, Nagpur"); break;
			}
			break;
			case 2: //Mumbai
			switch(mall){
				case 1: strcpy(mall_name,"R-City Mall, Mumbai"); break;
	    		case 2: strcpy(mall_name,"Inorbit Mall, Mumbai"); break;
	    		case 3: strcpy(mall_name,"Phoenix Mall, Mumbai"); break;
			}
			break;
	    	case 3: //Delhi
	    	switch(mall){
				case 1: strcpy(mall_name,"Ambience Mall, Delhi"); break;
	    		case 2: strcpy(mall_name,"DLF Mall, Delhi"); break;
	    		case 3: strcpy(mall_name,"Select city walk Mall, Delhi"); break;
			}
			break;
			case 4: //Bangalore
			switch(mall){
				case 1: strcpy(mall_name,"Central Mall, Bangalore"); break;
	    		case 2: strcpy(mall_name,"Orion Mall, Bangalore"); break;
	    		case 3: strcpy(mall_name,"Phoenix market city, Bangalore"); break;
			}
			break;
		}
		
		switch(time){
			case 1: strcpy(showtime,"9-AM"); break;
			case 2: strcpy(showtime,"2-PM"); break;
			case 3: strcpy(showtime,"6-PM"); break;
		}
		
		//seat_nos
		
		
		
		// inserting
		conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
    	
    	
    	char buf2[1024] = {};
	    char query_string2[] = {"insert into %s values (%d, '%s', '%s', '%s', %d);"};
	    
	    sprintf(buf2, query_string2,loginid,ticket_id,movie_id,mall_name,showtime,seat_nos);
	    
	    if (mysql_query(conn,buf2)) {
	    fprintf(stderr, "%s\n", mysql_error(conn));
	    exit(1);
	    }
	    mysql_close(conn);
	    
	    
	    // printing ticket
        printf("\t-----------------THEATER BOOKING TICKET----------------\n");
        printf("\t============================================================\n");
        printf("\t Booking ID : %d\t\t\tShow Name : %s\n",ticket_id,movie_name);
        printf("\t Customer  : %s\n",cus_name);
        printf("\t                                           Time      : %s\n",showtime);
        printf("\t                                           Screen    : %s\n",screen_no);
        printf("\t                                           seat No.  : %d  \n",seat_nos);
        printf("\t                                           price . : %s  \n\n",price);
        printf("\t============================================================\n");
	
	}
    }
	
}
int language(void)
{
	int j;
	printf("\t\t\tChoose your language\n");
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for Hindi\n\n");
	printf("\t\t\tpress 2 for English\n\n");
	printf("\t\t\tpress 3 for Marathi\n");
	
    scanf("%d",&j);
    return j;
}
int D (void)
{
	int a;
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for 2-D\n\n");
	printf("\t\t\tpress 2 for 3-D\n\n");

}
int malls(int city)
{
	int y;
	if(city==1)
	{
	printf("\t\t\t Choose Mall in Nagpur \n");
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for VR Mall\n\n");
	printf("\t\t\tpress 2 for Eternity Mall\n\n");
	printf("\t\t\tpress 3 for Empress Mall\n"); 
	scanf("%d",&y);
	}
	if(city==2)
	{ 
	printf("\t\t\t Choose Mall in Mumbai \n");
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for R-City Mall\n\n");
	printf("\t\t\tpress 2 for Inorbit Mall\n\n");
	printf("\t\t\tpress 3 for Phoenix Mall\n"); 
    scanf("%d",&y);	
	}
	if(city==3)
	{
    printf("\t\t\t Choose Mall in Delhi \n");
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for Ambience Mall\n\n");
	printf("\t\t\tpress 2 for DLF Mall\n\n");
	printf("\t\t\tpress 3 for Select city walk Mall\n"); 
	scanf("%d",&y);
	}
	if(city==4)
	{
	printf("\t\t\t Choose Mall in Bangalore \n");
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for Central Mall\n\n");
	printf("\t\t\tpress 2 for Orion Mall\n\n");
	printf("\t\t\tpress 3 for Phoenix market city\n"); 
	scanf("%d",&y);	
	}
	return y;
}
int time(void)
{
	int s;
	printf("\t\t\t Choose your timings\n");
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for 9 -12\n\n");
	printf("\t\t\tpress 2 for 2-5\n\n");
	printf("\t\t\tpress 3 for 6-9\n");
	scanf("%d",&s);
	return s; 
}

/// initial choices
int login_choice(void)
{
    printf("                     Movie Ticket Booking System\n");
    printf("                           Login Page\n");
    printf(" ==================================================================\n");
    printf("||                      1- Customer Login                         ||\n");
    printf("||                      2- Admin Login                            ||\n");
    printf("||                      3- Exit system                            ||\n");
    printf(" ==================================================================\n");
    printf("Enter Choice: ");
    int choice_login;
    scanf("%d", &choice_login);
    return choice_login;
}
int admin_settings(void)
{
    printf("                         Admin Settings\n");
    printf(" ==================================================================\n");
    printf("||                   1- Change ticket prices                      ||\n");
    printf("||                   2- Change Movie                              ||\n");
    printf("||                   3- Exit System                               ||\n");
    printf(" ==================================================================\n");
    printf("Enter Choice: ");
    int admin_settings_choice;
    scanf("%d", &admin_settings_choice);
    return admin_settings_choice;
}
int customer_settings(void)
{
    printf("                    Movie Ticket Booking System\n");
    printf(" ==================================================================\n");
    printf("||                      1- Book Ticket                            ||\n");
    printf("||                      2- View Tickets                           ||\n");
    printf("||                      3- Cancel Tickets                         ||\n");
    printf("||                      4- Exit System                            ||\n");
    printf(" ==================================================================\n");
    printf("Enter Choice: ");
    int customer_settings_choice;
    scanf("%d", &customer_settings_choice);
    return customer_settings_choice;
}



/*==========================================| CUSTOMER FUNCTIONS |==============================================*/

/// customer settings
int seats (void){
    int n,i,j;
    printf("===============|SCREEN THIS SIDE|==============\n\n\n");
    for (i=1; i<101; i++){
        if (i<11) printf("%d    ",i);
        else printf("%d   ",i);

        if (i%10==0) printf("\n\n\n");
    }
        printf("Enter the seat you want to book: ");
        scanf("%d",&n);
        
        return n;
    }
    

void view_ticket(char loginid[30]){
	char movie_name[20],mall_name[40],ticket_id[3],showtime[5],seat_no[3],movie_id[5],price[5],cus_name[20],screen_no[3];
	
   
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    // first booking or not
    conn = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if(mysql_query(conn,"Show tables;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    int count=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],loginid)==0) { 
    count++;
    mysql_close(conn);
   
    }
    system("cls");
    int k;
    printf("\t               Retrieving tickets");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	printf("\t               Retrieving tickets");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
    
    
    if (count==0) printf("You haven't booked any tickets yet!");
    else if (count==1){
    	
    	// number of rows (tickets)
    	//ticket id
		conn = mysql_init(NULL);
    	/* Connect to database */
	    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
	    {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	    char buf3[1024] = {};
		    char query_string3[] = {"select ticket_id from %s;"};
		    
		    sprintf(buf3, query_string3,loginid);
		    
		    if (mysql_query(conn,buf3)) {
		    fprintf(stderr, "%s\n", mysql_error(conn));
		    exit(1);
		}
	    res=mysql_use_result(conn);
	    int tickets=0;
	    while ((row= mysql_fetch_row(res)) != NULL){ 
		tickets++ ;}
		mysql_close(conn);
		
		int i,j;
		for(i=1; i<=tickets; i++){
			
			// mall_name
			conn = mysql_init(NULL);
	    	/* Connect to database */
		    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
		    {
		        fprintf(stderr, "%s\n", mysql_error(conn));
		        exit(1);
		    }
		    char buf[1024] = {};
			    char query_string[] = {"select ticket_id,movieid,mall_name,time,seats from %s;"};
			    
			    sprintf(buf, query_string,loginid);
			    
			    if (mysql_query(conn,buf)) {
			    fprintf(stderr, "%s\n", mysql_error(conn));
			    exit(1);
			}
		    res=mysql_use_result(conn);
		    
		    for (j=1; j<=i; j++){
		    	row= mysql_fetch_row(res);
			}
			strcpy(ticket_id, row[0]);
			strcpy(movie_id,row[1]);
			strcpy(mall_name,row[2]);
			strcpy(showtime,row[3]);
			strcpy(seat_no,row[4]);
			
			mysql_close(conn);
			
			
			//extracting movie name and screen number
			conn = mysql_init(NULL);
	    	/* Connect to database */
		    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
		    {
		        fprintf(stderr, "%s\n", mysql_error(conn));
		        exit(1);
		    }
		    char buff[1024] = {};
			    char query_stringg[] = {"select movie_name, screen_no from movies where movie_id='%s';"};
			    
			    sprintf(buff, query_stringg,movie_id);
			    
			    if (mysql_query(conn,buff)) {
			    fprintf(stderr, "%s\n", mysql_error(conn));
			    exit(1);
			}
		    res=mysql_use_result(conn);
		    row= mysql_fetch_row(res);
		    strcpy(movie_name,row[0]);
		    strcpy(screen_no,row[1]);
		    mysql_close(conn);
		    
		    
		    // extracting ticket price
		    conn = mysql_init(NULL);
	    	/* Connect to database */
		    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
		    {
		        fprintf(stderr, "%s\n", mysql_error(conn));
		        exit(1);
		    }
		    char buff2[1024] = {};
			    char query_stringg2[] = {"select seat_price from price where movie_id='%s';"};
			    
			    sprintf(buff2, query_stringg2,movie_id);
			    
			    if (mysql_query(conn,buff2)) {
			    fprintf(stderr, "%s\n", mysql_error(conn));
			    exit(1);
			}
		    res=mysql_use_result(conn);
		    row= mysql_fetch_row(res);
		    strcpy(price,row[0]);
		    mysql_close(conn);
		    
		    
		    //extracting customer name
		    conn = mysql_init(NULL);
	    	/* Connect to database */
		    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
		    {
		        fprintf(stderr, "%s\n", mysql_error(conn));
		        exit(1);
		    }
		    char buff3[1024] = {};
			    char query_stringg3[] = {"select cus_name from login where login_id='%s';"};
			    
			    sprintf(buff3, query_stringg3,loginid);
			    
			    if (mysql_query(conn,buff3)) {
			    fprintf(stderr, "%s\n", mysql_error(conn));
			    exit(1);
			}
		    res=mysql_use_result(conn);
		    row= mysql_fetch_row(res);
		    strcpy(cus_name,row[0]);
		    mysql_close(conn);
		    
		    
		    // printing ticket
	        printf("\t-----------------THEATER BOOKING TICKET----------------\n");
	        printf("\t============================================================\n");
	        printf("\t Booking ID : %s\t\t\tShow Name : %s\n",ticket_id,movie_name);
	        printf("\t Customer  : %s\n",cus_name);
	        printf("\t                                           Time      : %s\n",showtime);
	        printf("\t                                           Screen    : %s\n",screen_no);
	        printf("\t                                           seat No.  : %s  \n",seat_no);
	        printf("\t                                           price . : %s  \n\n",price);
	        printf("\t============================================================\n");
	        
	        printf("\n\n");		
		}
	    
	}
    
}
}
void cancel_ticket(char login_id[20])
{
	int ticket_id;
	system("cls");
     printf("Enter ticket id of the booking you want to cancel: ");
     scanf("%d",&ticket_id);
     
     MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    
    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "customer", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char buf[1024] = {};
    char query_string[] = {"delete from %s where ticket_id=%d"};
    sprintf(buf, query_string,login_id,ticket_id);
    
    if (mysql_query(conn,buf)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
    }
    mysql_close(conn);
    
    system("cls");
    
    int k;
    printf("\t               Cancelling ticket");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	printf("\t               Cancelling ticket");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  
	  system("cls");
	  
	printf("\t         Your ticket was cancelled successfully!");
    
     
     
}
int location_city(void){
    printf("                             LOCATION\n");
    printf(" ==================================================================\n");
    printf("||                          1- Nagpur                             ||\n");
    printf("||                          2- Mumbai                             ||\n");
    printf("||                          3- Delhi                              ||\n");
    printf("||                          4- Bangalore                          ||\n");
    printf(" ==================================================================\n");
    printf("Enter Choice: ");
    int location_choice;
    scanf("%d",&location_choice);
    return location_choice;
}

/// customer login
int customer_login(void){
    printf("                          Customer Login\n");
    printf(" ==================================================================\n");
    printf("||                          1- Exisitng User?                     ||\n");
    printf("||                          2- New User                           ||\n");
    printf("||                          3- Exit System                        ||\n");
    printf("||                          4- Go back                            ||\n");
    printf(" ==================================================================\n");
    printf("Enter Choice: ");
    int customer_type;
    scanf("%d",&customer_type);
    return customer_type;
}

int existing_customer(char login_id[30]){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
   
    char password[20];
    printf("Welcome Back!\n\n");
    printf("Enter Login Id: ");
    scanf("%s",login_id);
    
    
    
    
    system("cls");

    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if(mysql_query(conn,"Select login_id from login;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    
    //row= mysql_fetch_row(res);
    int count1=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],login_id)==0) { 
    count1++;
}}
    mysql_close(conn);
    
    if (count1==0) { 
                return 2;
				}
                
    if (count1==1){
    
    // welcome user
    conn = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char buf[1024] = {};
    char query_string[] = {"select cus_name from login where login_id='%s'"};
    sprintf(buf, query_string,login_id);
    
    if (mysql_query(conn,buf)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
    }
    res=mysql_use_result(conn);
    row= mysql_fetch_row(res);
    
    printf("Welcome %s!\n\n",row[0]);
    printf("Enter Password: ");
    

    //scanning password
    int m=0;
    while(m<20)
	{
	    password[m]=getch();
	    if(password[m]==13) break;
	    else if(password[m]==8){
	    	system("cls");
	    	printf("Welcome %s!\n\n",row[0]);
            printf("Enter Password: ");
            m--;
            int n;
            for(n=0; n<m; n++){
            	printf("*");
			}
		}
	    else {
		printf("*");
		m++;
		}
	}
	password[m]='\0';
    system("cls");
	
	
	
	
    mysql_close(conn);
    
    conn = mysql_init(NULL);
    

    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if(mysql_query(conn,"Select login_id,pass_word from login;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    
    //row= mysql_fetch_row(res);
    int count=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],login_id)==0 && strcmp(row[1],password)==0) { 
    count++;
   
}
    
     }
     
     // logging you in
      printf("Logging you in");
      int k;
      for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	  printf("Logging you in");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
     
     
     if (count==1) return 1;
     else if (count==0) return 2;     
    
    mysql_free_result(res);
    mysql_close(conn);
  
}}
int new_customer(void){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    
    printf("Welcome to our site.. :)\n");
    printf("Enter your details and plug into the nirvana.. :)\n\n");
    
    char cus_name[20],cus_email[30],login_id[20],password[20];
    
    // removing buffer
    char c;
do{
    c = getchar();
}while(c != EOF && c != '\n');
    
    
    printf("Enter your name: ");
    fgets(cus_name,20,stdin);

    cus_name[strlen(cus_name)-1]='\0';
    
    printf("Enter you email: ");
    scanf("%s",cus_email);
    
    
    printf("\nMake yourselve a unique login id.. For you next visit..: ");
    scanf("%s",login_id);
    
     /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
        if(mysql_query(conn,"Select login_id from login;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    
    //row= mysql_fetch_row(res);
    int count=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],login_id)==0) {
   // printf("Sorry!! This login id already exists. \n Kindly enter a differnt one. \n");  
    count++;
     }}
    if (count==1) {
    system("cls");
	printf("Sorry! This login id already exists. Kindly enter a differnt one. \n");
	exit(0);
	}
    else if (count==0) {
	printf("Login Id confirmed!\n");}
		
    mysql_free_result(res);
    mysql_close(conn);

    printf("Enter a secure password for your new account: ");
    scanf("%s",password); 
    
    conn = mysql_init(NULL);
      /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char buf[1024] = {};
    char query_string[] = {"insert into login values('%s','%s','%s','%s')"};
    sprintf(buf, query_string,login_id,cus_name,cus_email,password);
    
    if (mysql_query(conn,buf)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
    }
    mysql_close(conn);

    
    system("cls");
    printf("Account Created Successfully!! :) \n\n");
    printf("Hold onto your seats for the immersive experience!! :) ");
    
    int z;
      for (z=1; z<6; z++){
      	usleep(200000);
      	printf(".");
	  }
	  
	  system("cls");
    
    
    
    printf("Kindly login to continue \n\n");
    
    conn = mysql_init(NULL);
    
    printf("Enter Login Id: ");
    scanf("%s",login_id);
        system("cls");
    
    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if(mysql_query(conn,"Select login_id from login;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    
    //row= mysql_fetch_row(res);
    int count1=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],login_id)==0) { 
    count1++;
}}
    if (count1==0) {printf("user id doesn''t exist"); return 6;
	}
	else if (count1==1){
    
    // welcome user
    conn = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char buf2[1024] = {};
    char query_string2[] = {"select cus_name from login where login_id='%s'"};
    sprintf(buf2, query_string2,login_id);
    
    if (mysql_query(conn,buf2)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
    }
    res=mysql_use_result(conn);
    row= mysql_fetch_row(res);
    
    printf("Welcome %s!\n\n",row[0]);
    
    
    
    printf("Enter Password: ");
    
    int m=0;
    while(m<20)
	{
	    password[m]=getch();
	    if(password[m]==13) break;
	    else if(password[m]==8){
	    	system("cls");
	    	printf("Welcome %s!\n\n",row[0]);
            printf("Enter Password: ");
            m--;
            int n;
            for(n=0; n<m; n++){
            	printf("*");
			}
		}
	    else {
		printf("*");
		m++;
		}
	}
	password[m]='\0';
    system("cls");
    
    mysql_close(conn);
    
    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if(mysql_query(conn,"Select login_id,pass_word from login;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    
    //row= mysql_fetch_row(res);
    
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],login_id)==0 && strcmp(row[1],password)==0) {
    count++;
   
      }
    
     }
     
     // logging you in
      printf("Logging you in");
      int k;
      for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	  printf("Logging you in");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
     
     
     if (count==1) return 1;
     else if (count==0) return 2;     
    
    mysql_free_result(res);
    mysql_close(conn);
    
}}


                                                          
/*===========================================| ADMIN FUNCTIONS |================================================*/
/// admin settings
int admin_login(void){
	printf("Welcome to admin login.. :\n\n");
	
	char admin_name[20],password[20];
	
	printf("Enter your name: ");
	scanf("%s",admin_name);
    
    printf("Enter your password: ");
	int m=0;
    while(m<20)
	{
	    password[m]=getch();
	    if(password[m]==13) break;
	    else if(password[m]==8){
	    	system("cls");
	    	printf("Welcome to admin login.. :\n\n");
	    	printf("Enter your name: %s\n",admin_name);
            printf("Enter Password: ");
            m--;
            int n;
            for(n=0; n<m; n++){
            	printf("*");
			}
		}
	    else {
		printf("*");
		m++;
		}
	}
	password[m]='\0';
    system("cls");
    
    // logging you in
      printf("Logging you in");
      int k;
      for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	  printf("Logging you in");
	  for (k=1; k<6; k++){
      	usleep(200000);
      	printf(".");
	  }
	  system("cls");
	
	MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
	
	/* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if(mysql_query(conn,"Select admin_name,admin_pass from sys_admin;"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    

    int count=0;
    while ((row= mysql_fetch_row(res)) != NULL){  
    if (strcmp(row[0],admin_name)==0 && strcmp(row[1],password)==0) {  
    count++;
   
}
    
     }
     if (count==1) return 1;
     else if (count==0) return 2;     
    
    mysql_free_result(res);
    mysql_close(conn);
}
void change_price(void){
    char movieid[20],seatprice[20];

    printf("Enter movie id whose price you want to change: ");
    scanf("%s",movieid);
    
    printf("Enter price of the seat: ");
    scanf("%s",seatprice);
    
    system("cls");
    
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);

/* Connect to database */
    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    char buf[1024] = {};
    char query_string[] = {"update price set seat_price='%s' where movie_id='%s';"};
    sprintf(buf, query_string,seatprice,movieid);
    
    if (mysql_query(conn,buf)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
    }
    res=mysql_use_result(conn);
    mysql_close(conn);
    printf("Your price has been updated!\n\n");

}
void change_movie(void){
	int choice,screen_no,price;
	char movie_id[10],movie_name[20],language[10],definition[2],variable[20],variable_val[20];
	
	hi:
    printf("What do you want to change?\n");

    printf("1. Remove a movie\n");
    printf("2. Add a movie\n");
    printf("3. Edit details of a movie\n");
    printf("Enter Choice: ");
    scanf("%d",&choice);
    system("cls");
    switch(choice){
    	
    	
    	// remove movie
    	
    	case 1: printf("Enter the movie id you wish to remove: ");
    	        scanf("%s",&movie_id);
				MYSQL *conn;
			    MYSQL_RES *res;
			    MYSQL_ROW row;
			    conn = mysql_init(NULL);
				
				/* Connect to database */
			    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
			    {
			        fprintf(stderr, "%s\n", mysql_error(conn));
			        exit(1);
			    }
			
			    char buf[1024] = {};
			    char query_string[] = {"delete from movies where movie_id='%s';"};
			    sprintf(buf, query_string,movie_id);
			    
			    if (mysql_query(conn,buf)) {
			    fprintf(stderr, "%s\n", mysql_error(conn));
			    exit(1);
		    	}
		    	
		    	printf("Movie has been deleted successfully!\n\n");
		    	
		    	break;
		    	
		    	
		    	
		// add movie
		
		case 2: printf("Enter the details of the movie!\n");
		        printf("Enter a unique movie id: ");
		        scanf("%s",&movie_id);
		        
		     
			    conn = mysql_init(NULL);
			    
			    
			    /* Connect to database */
			    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
			    {
			        fprintf(stderr, "%s\n", mysql_error(conn));
			        exit(1);
			    }
			    
			    
			    if(mysql_query(conn,"Select movie_id from movies;"))
			    {
			        fprintf(stderr, "%s\n", mysql_error(conn));
			        exit(1);
			    }
			    
			    
			    res=mysql_use_result(conn);
			    
			    int count=0;
			    while ((row= mysql_fetch_row(res)) != NULL){  
			    if (strcmp(row[0],movie_id)==0) {
			    count++;
		    	}}
		    	mysql_close(conn);
			    if (count==1) printf("Sorry!! This movie id already exists. \n Kindly enter a differnt one. \n");
			    else if (count==0) 
				{
					
					// removing buffer
					    char c;
					do{
					    c = getchar();
					}while(c != EOF && c != '\n');
					    
					
			       printf("Enter Movie name: ");
			       fgets(movie_name,20,stdin);
			       movie_name[strlen(movie_name)-1]='\0';
			       printf("Enter Screen Number: ");
			       scanf("%d",&screen_no);
			       printf("Enter Language of movie: ");
			       scanf("%s",&language);
			       printf("Enter movie viewing dimension (2D/3D): ");
			       scanf("%s",&definition);
			       printf("Enter price of movie ticket: ");
			       scanf("%d",&price);
			       
			       conn = mysql_init(NULL);
			    
			    
				    /* Connect to database */
				    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
				    {
				        fprintf(stderr, "%s\n", mysql_error(conn));
				        exit(1);
				    }
			       char buf[1024] = {};
			       char query_string[] = {"insert into movies values('%s','%s',%d,'%s','%s');"};
			       sprintf(buf, query_string,movie_id,movie_name,screen_no,language,definition);
			    
			       if (mysql_query(conn,buf)) {
			       fprintf(stderr, "%s\n", mysql_error(conn));
			       exit(1);
			       
		    	    }	     
				
			    mysql_close(conn);
			    
			    
			    conn = mysql_init(NULL);
			    
			    
				    /* Connect to database */
				    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
				    {
				        fprintf(stderr, "%s\n", mysql_error(conn));
				        exit(1);
				    }
			       char buff[1024] = {};
			       char query_stringg[] = {"insert into price values('%s','%s',%d);"};
			       sprintf(buff, query_stringg,movie_id,definition,price);
			    
			       if (mysql_query(conn,buff)) {
			       fprintf(stderr, "%s\n", mysql_error(conn));
			       exit(1);
		    	    }
					mysql_close(conn);
					system("cls");	  
					printf("Movie added successfully!\n\n");  
		        	}
			    break;
			    
			    
		case 3: printf("Which movie's details do you want to change? Enter it's Movie ID: ");
		        scanf("%s",&movie_id);
		        
		        conn = mysql_init(NULL);
			    
			    
			    /* Connect to database */
			    if (!mysql_real_connect(conn, "localhost", "root", "Gaur@123#", "cp_project", 0, NULL, 0))
			    {
			        fprintf(stderr, "%s\n", mysql_error(conn));
			        exit(1);
			    }
			    
			    
			    if(mysql_query(conn,"Select movie_id from movies;"))
			    {
			        fprintf(stderr, "%s\n", mysql_error(conn));
			        exit(1);
			    }
			    
			    
			    res=mysql_use_result(conn);
			    
			    count=0;
			    while ((row= mysql_fetch_row(res)) != NULL){  
			    if (strcmp(row[0],movie_id)==0) {
			    count++;
		    	}}
			    if (count==0) printf("Sorry!! A movie with this movie ID doesn't exist!\n");
			    else {
			    	printf("What do you want to change?\n");
			    	printf("1- Movie Name\n");
			    	printf("2- Screen Number\n");
			    	printf("3- Language\n");
			    	printf("4- Movie definition\n");
			    	printf("Enter choice: ");
			    	scanf("%d",&choice);
			    	system("cls");
			    	if (choice==1){
			    		        strcpy(variable,"movie_name");
			    		        printf("Enter new movie name: ");
			    		        scanf("%s",&variable_val);
			    		        }
			    	else if (choice==2){
					
			    		        printf("Enter updated screen: ");
			    		        
								scanf("%s",&variable_val);
			    		        strcpy(variable,"screen_no");
								}
			    	else if(choice==3){
					            strcpy(variable,"bhasha");
			    		        printf("Enter updated language: ");
			    		        scanf("%s",&variable_val);
			    		        }
			    	else if(choice==4){
					            strcpy(variable,"movie_veiwing_type");
			    		        printf("Enter movie dimension: ");
			    		        scanf("%s",&variable_val);
			    		        }
			    	else printf("Invalid Input");
				        
				    
				    char buf[1024] = {};
				    
				    if (choice==2){
					
			       char query_string[] = {"update movies set %s=%s where movie_id='%s';"};
			       sprintf(buf, query_string,variable,variable_val,movie_id);
			       
			    
			       if (mysql_query(conn,buf)) {
			       fprintf(stderr, "%s\n", mysql_error(conn));
			       exit(1);
			       }
		    	    }
					else {
						char query_string[] = {"update movies set %s='%s' where movie_id='%s'"};
			       sprintf(buf, query_string,variable,variable_val,movie_id);
			    
			       if (mysql_query(conn,buf)) {
			       fprintf(stderr, "%s\n", mysql_error(conn));
			       exit(1);
			        }
					}
					printf("Movie details updated successfully!\n\n");
						    
		    	    
				}
				mysql_free_result(res);
			    mysql_close(conn);
			    break;
		        
		default: printf("Invalid Input! Kindly try again!\n\n");
		         goto hi;        
			    
			
}
    	        
    	        
	
    

    

}








//=======================================|MAIN|===============================================//

int main()
{
    /// DECLARATIONS 
    int login_type,location,city,customer_type,customer_work,admin_work,login_access,movie_name,bhasha,
    D_type,mall_name,showtime,seat_select;
    char loginid[30];
    
    while(1){
	int chc;

    login_type = login_choice();
    system("cls");
    /// login type protocols


/*=============================================| CUSTOMER LOGIN |================================================*/

            if (login_type == 1)                                             
             {
             	while(1){
                customer_type = customer_login();
                system("cls");
                    /// existing or new
                    

                        if (customer_type==1)                           /// EXISTING CUSTOMER
                         {  
                          login_retry:
                            login_access=existing_customer(loginid);
                            
                            
                            if (login_access==1)         /// access granted
                               {
                               	 printf("Login Successfull!");
                               	 usleep(600000);
                               	 system("cls");
                               	 
                                 city = location_city();    /// which city
                                 system("cls");
								 customer_settings:
                                 customer_work = customer_settings();
                                 system("cls");
                                    /// WHAT CUSTOMER WANTS TO DO :

                                    if (customer_work==1)       /// book a ticket
                                     {
                                       movie_name=movie(); system("cls");
                                       mall_name=malls(city); system("cls");
                                       showtime=time(); system("cls");
                                       seat_select=seats(); system("cls");
                                       generate_ticket(movie_name,mall_name,city,showtime,loginid,seat_select);
                                       printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) goto customer_settings;  
										else continue;}
										
                                       
                                       
                                     }
                                    else if (customer_work==2)  /// view tickets
                                     {
                                       view_ticket(loginid);
                                       printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) goto customer_settings;  
										else continue;}
                                       
                                     }
                                    else if (customer_work==3)  /// cancel ticket
                                     {
                                       cancel_ticket(loginid);
                                       printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) goto customer_settings;  
										else continue;}
                                     }
                                    else if (customer_work==4) {printf("Thank You!");
									exit(0);}  /// exit

                                    else {
									printf("Invalid Input!\n\n");
									goto customer_settings;}
                               }

                            else if (login_access==2) {printf("Invalid User Id or Password! Do you want to try again?\n");   /// access denied
                                        printf("1- Retry\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto login_retry;
										else if (chc==2) break;  
										else continue;}
										}
						 }
                        else if (customer_type==2)                      /// NEW CUSTOMER
                         {
                            login_access=new_customer();
                            if (login_access==1)       /// access granted
                               {
                               	 printf("Login Successfull!");
                               	 usleep(600000);
                               	 system("cls");
                               	 
                                 city = location_city();    /// which city
                                 system("cls");
								new_customer:
                                 customer_work = customer_settings();
                                 system("cls");
                                    /// WHAT CUSTOMER WANTS TO DO :

                                    if (customer_work==1)       /// book a ticket
                                     {
                                       movie_name=movie(); system("cls");
                                       mall_name=malls(city); system("cls");
                                       showtime=time(); system("cls");
                                       seat_select=seats(); system("cls");
                                       generate_ticket(movie_name,mall_name,city,showtime,loginid,seat_select);
                                       printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) goto new_customer;  
										else continue;}
                                     }
                                    else if (customer_work==2)  /// view tickets
                                     {
                                       view_ticket(loginid);
                                       printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) goto new_customer;  
										else continue;}
                                     }
                                    else if (customer_work==3)  /// cancel ticket
                                     {
                                       cancel_ticket(loginid);
                                       printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) goto new_customer;  
										else continue;}
                                     }
                                    else if (customer_work==4) {printf("Thank You!");
									exit(0);}  /// exit

                                    else {
									printf("Invalid Input!\n\n");
									goto new_customer;}
                               }

                            else {printf("Invalid User Id or Password! Do you want to try again?\n");   /// access denied
                                        printf("1- Retry\n2- Go back\n");
										int chc;
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto login_retry;
										else if (chc==2) break;  
										else continue;}
										}   
                         }

                        else if (customer_type==3)      /// exit
                         {terminate_function:
                            printf("Thank You!");
                            
                            exit(0);
                         }
                         else if (customer_type==4) break;
                        else {
						printf("Invalid Input! Kindly try again!\n\n");
						continue;}
                
             }}





/*==============================================| ADMIN LOGIN |==================================================*/

            else if (login_type==2)                                              
             {
             	while(1){
				 
                login_access=admin_login();
                if (login_access==1)              /// access granted
                    {
                    	while(1){
						
                       admin_work=admin_settings();
                       system("cls");
                           /// WHAT ADMIN WANTS TO DO :

                           if (admin_work==1)       /// change ticket prices
                            {
                              change_price();
                              printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) break;  
										else continue;}
                            }
                           else if (admin_work==2)  /// change movies available
                            {
                              change_movie();
                              printf("\n1- Exit System\n2- Go back\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) goto terminate_function;
										else if (chc==2) break;  
										else continue;}
                            }

                           else if (admin_work==3) {  /// exit
                               goto terminate_function;}

                           else printf("Invalid Input!\n\n");
                   } }

                else{
				
                       printf("Invalid User Id or Password!");     /// access denied
                       printf("\n1- Retry\n2- Exit System\n");
										while(1){
										scanf("%d",&chc);
										system("cls");
										if (chc==1) break;
										else if (chc==2) {printf("Thank You!"); exit(0);}
										else continue;}
             }}}

            else if (login_type==3)
             {
                printf("Thank You!");
                break;
             }

            else 
			{printf("Invalid Input! Kindly try again\n\n");
			continue;}
			
}}
