#include<stdio.h>//BT21CSE96,BT21CSE0100
#include<string.h>
#define date 3
struct city{
double sky_view_factor;
double vegetation_density_ratio;
double population_density;
double pervious_surface_fraction;
double impervious_surface_fraction;
char station_status[5];
float distance[100];
float air_temperature[date];
float relative_humidity[date];
};
void heat_island_intensity(struct city st[],int n){
float minrural=999999,heat_island_intensity=0,urban_avg=0,rural_avg=0;
int minruralst_num=0,count=0,secondminruralst_num=0,i,j;
for(i=0;i<n;i++){
	if(strcmp(st[i].station_status,"urban")==0){
for(j=0;j<n;j++){
        if(strcmp(st[j].station_status,"rural")==0){
		if(st[j].distance[i]<=minrural){
		count++;
		if(count==2 && minrural==st[j].distance[i]){
		secondminruralst_num= minruralst_num;	
		}
    	 minrural=st[j].distance[i];
		 minruralst_num=j;	
		}	
        }
        }
  if(secondminruralst_num!=0){
  if(st[secondminruralst_num].pervious_surface_fraction>st[minruralst_num].pervious_surface_fraction){
	minruralst_num=secondminruralst_num;
       }
       }
for(j=0;j<date;j++){
	urban_avg=urban_avg+st[i].air_temperature[j];
	rural_avg=rural_avg+st[minruralst_num].air_temperature[j];
      }
urban_avg=(urban_avg/(date*1.0));
rural_avg=(rural_avg/(date*1.0));
heat_island_intensity=urban_avg-rural_avg;
printf("THE HEAT ISLAND INTENSITY IS %f for station-%d \n",heat_island_intensity,i+1);
      }
minrural=999999;
heat_island_intensity=0;
count=0;
secondminruralst_num=0;
minruralst_num=0;
urban_avg=0;
rural_avg=0;
}
}
void veg_density(struct city st[],int n,float average_city_temperature){
int i,j,sorted=0,station_no[n];
double veg_density[n];
for(i=0;i<n;i++){
station_no[i]=i;
}
for(i=0;i<n;i++){
 veg_density[i]=st[i].vegetation_density_ratio;
}
for(i=0;i<n-1 && sorted==0;i++){
sorted=1;
for(j=0;j<n-i-1;j++){
if(veg_density[j]<veg_density[j+1]){
double temp=veg_density[j];
veg_density[j]=veg_density[j+1];
veg_density[j+1]=temp;
int tempo=station_no[j];
station_no[j]=station_no[j+1];
station_no[j+1]=tempo;
sorted=0;
}
}
}
printf("THE AVERAGE CITY TEMPERATURE IS %f",average_city_temperature);
for(i=0;i<n;i++){
printf("-------------------------------------------------------------------------------------\n");
printf("STATION-%d\n",station_no[i]+1);
for(j=0;j<date;j++){
 if(st[station_no[i]].air_temperature[j]>average_city_temperature){
 	printf("DAY-%d with %f\n",j+1,st[station_no[i]].air_temperature[j]);
 }
}
}
}
void minpopuldensity(struct city st[],int n,int k){
int i,j,sorted=0,m,station_no[n];
double popul_dens[n];
for(i=0;i<n;i++){
station_no[i]=i;
}
for(i=0;i<n;i++){
popul_dens[i]=st[i].population_density;	
}
float max1=-9999999,max2=-9999999;
for(i=0;i<n-1 && sorted==0;i++){
sorted=1;
for(j=0;j<n-i-1;j++){
if(popul_dens[j]>popul_dens[j+1]){
int tempo=station_no[j];
station_no[j]=station_no[j+1];
station_no[j+1]=tempo;
sorted=0;
double temp=popul_dens[j];
popul_dens[j]=popul_dens[j+1];
popul_dens[j+1]=temp;
}
}
}
for(j=0;j<n-1;j++){
if(st[station_no[j]].population_density==st[station_no[j+1]].population_density){ 
for(m=0;m<date;m++){
	if(st[station_no[j]].air_temperature[m]>max1){
	 max1=st[station_no[j]].air_temperature[m];
	}
	if(st[station_no[j+1]].air_temperature[m]>max2){
	 max2=st[station_no[j+1]].air_temperature[m];
	}
}
if(max1<max2){
int tempo=station_no[j];
station_no[j]=station_no[j+1];
station_no[j+1]=tempo;
}
max1=-9999999;
max2=-9999999;
}
}
for(i=0;i<k;i++){
 printf("station-%d\n",station_no[i]+1);	
}
}	
int main(){
int n,i,j,ch,station,minruralst_num=0,flag=0,check=0;
float minrural=999999,tempmin=999999,average_city_temperature=0,diff;
printf("Enter the number of Climate Stations in city: ");
scanf("%d",&n);
struct city st[n],stemp[n];
for(i=0;i<n;i++){
printf("-------------------------------------------------------------------------------------\n");
printf("\t\t STATION-%d\n",i+1);
printf("Enter the value of Sky View factor(0.1-0.9): ");
scanf("%lf",&st[i].sky_view_factor);
printf("Enter the value of vegetation density ratio(percentage): ");	
scanf("%lf",&st[i].vegetation_density_ratio);
printf("Enter the value of Population density(Number of people per Sq. km): ");
scanf("%lf",&st[i].population_density);
printf("Enter the value of pervious surface fraction(0-15): ");
scanf("%lf",&st[i].pervious_surface_fraction);
printf("Enter the value of impervious surface fraction(0-15): ");
scanf("%lf",&st[i].impervious_surface_fraction);
printf("Enter station status(rural/urban): ");
scanf("%s",st[i].station_status);
printf("Enter Distance of station-%d to other stations (in km) : \n",i+1);
for(j=i+1;j<n;j++){
printf("S-%d ",j+1);
}
printf("\n");
for(j=0;j<n;j++){
if(j==i){
  st[i].distance[j]=0;
}	
if(j>i){
scanf("%f",&st[i].distance[j]);
}
if(j<i){
st[i].distance[j]=st[j].distance[i];
}
}
printf("     TEMP REL_HUMIDITY\n");
for(j=0;j<date;j++){
printf("Day%d ",j+1);
scanf("%f",&st[i].air_temperature[j]);
scanf("%f",&st[i].relative_humidity[j]);
}
}
printf("-------------------------------------------------------------------------------------\n");
 do
     {
          printf("\t\tMENU");
          printf("\n-------------------------------------\n");
          printf("PRESS 1.To List the stations with highest heat degree days");
          printf("\nPRESS 2.For any searched station,to find the thermally comfortable days.");
          printf("\nPRESS 3.To List dates for all stations with decreasing vegetation density ratio and for which the temperature was more than average city temperature");
          printf("\nPRESS 4.To List the (top 'k', k-input) stations with minimum population density with highest maximum temperature");
          printf("\nPRESS 5.To find the heat island intensity for all urban stations");
          printf("\nPRESS 6.TO EXIT.");
          printf("\n-------------------------------------\n");
          printf("Enter Your Choice: ");
          scanf("%d",&ch);
switch(ch){
	case 1:{
		int i,j;
		for(i=0;i<n;i++){
		for(j=0;j<date;j++){
		average_city_temperature+=st[i].air_temperature[j];
		}
		}
		average_city_temperature=(average_city_temperature/(n*date*1.0));
	printf("THE AVERAGE CITY TEMPERATURE IS %f\n",average_city_temperature);
		printf("\t\t HIGHEST HEAT DEGREE DAYS OF ALL STATIONS\n");
		for(i=0;i<n;i++){
         	printf("\n-------------------------------------\n");
			printf("STATION: %d\n",i+1);		
		for(j=0;j<date;j++){
			if(st[i].air_temperature[j]>average_city_temperature){
			 printf("Day %d with temperature %f\n",j+1,st[i].air_temperature[j]);
			}
            }
            }
		break;
}
case 2:{
	        printf("Enter the Station number for which you want to find Thermally Comfortable days: ");
	        scanf("%d",&station);
    for(i=0;i<n;i++){
        if(i+1==station){
        if(strcmp(st[i].station_status,"urban")==0){
    for(j=0;j<n;j++){
        if(strcmp(st[j].station_status,"rural")==0){
    	if(st[j].distance[i]<minrural){
    	 minrural=st[j].distance[i];
		 minruralst_num=j;	
		}
	    }	
	    }	
	    }
	    else{
	    	printf("IT IS A RURAL STATION.PLEASE ENTER URBAN STATION NUMBER\n");
	    	flag=1;
       }
       }
       }
if(flag==0){
	printf("THE NEARBY RURAL STATION FOR GIVEN URBAN STATION IS STATION-%d\n",minruralst_num+1);
    for(j=0;j<date;j++){
     if(st[station-1].air_temperature[j]>=st[minruralst_num].air_temperature[j]){
     diff=st[station-1].air_temperature[j]-st[minruralst_num].air_temperature[j];
	 }
	 else{
	 diff=st[minruralst_num].air_temperature[j]-st[station-1].air_temperature[j];
	 }
	if(diff<tempmin){
		tempmin=diff;
	}	
	}
	for(j=0;j<date;j++){
     if(st[station-1].air_temperature[j]-st[minruralst_num].air_temperature[j]==tempmin){   
     printf("DAY %d WITH MINIMUM TEMPERATURE %f\n",j+1,tempmin);

}
    else if(st[minruralst_num].air_temperature[j]-st[station-1].air_temperature[j]==tempmin){   
     printf("DAY %d WITH MINIMUM TEMPERATURE %f\n",j+1,tempmin);
}
}
}
	break;
}
case 3:{
	int i,j;
	float average_city_temperature=0;
		for(i=0;i<n;i++){
		for(j=0;j<date;j++){
		average_city_temperature+=st[i].air_temperature[j];
		}
		}
		average_city_temperature=(average_city_temperature/(n*date*1.0));
	veg_density(st,n,average_city_temperature);
	break;
}
case 4:{
	int k;
	printf("Enter the number of input stations:");
	scanf("%d",&k);
	minpopuldensity(st,n,k);
	break;
}
case 5:{
	heat_island_intensity(st,n);
	break;
}
}
}while(ch!=6);
}
