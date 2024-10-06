#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define widthMap 30
#define heightMap 50
#define fileMapLength 100
#define maps 100

const char fileMap[fileMapLength] = "file-map/";
const char dataHolder[fileMapLength] = "data-holder/";
const char mapList[fileMapLength] = "map-List.txt"; 

typedef struct{
	char fileName[fileMapLength];
	char fileLocation[fileMapLength];
	char newPath[fileMapLength];
	int minimumSteps;
	int possiblePath;
	int width;
	int height;
	// 0 for row and 1 for column
	int startPosition[2]; 
	int endPosition[2];
}data_Map; 

data_Map newPathData[maps];
int newPathCount;

int insideMap(data_Map data, int row, int column){
	if(row < data.height && row >= 0 && column < data.width && column >= 0){
		return 1;
	}else{
		return 0;
	}
}

int shortestPath(data_Map* data, char* map, int* data_move, int* data_distance, int row, int column, int distance){
	// row column
	int next[4][2] ={ 
		{-1, 0}, // up
		{0, 1}, // right
		{1, 0}, // down
		{0, -1}, // left
	};
	
	for(int i=0; i<4;i++){ 
		int nextRow = row + next[i][0];
		int nextColumn = column + next[i][1];
		int nextDistance = distance + 1;
		if(insideMap(*data, nextRow, nextColumn)){
			if(*(map + nextColumn + (data->width * nextRow)) == '#'){ 
				continue;
			}
			
			if(*(map + nextColumn + (data->width * nextRow)) == 'X'){ 
				if(data->minimumSteps > nextDistance || data->minimumSteps == -1){
					data->minimumSteps = nextDistance;
					data->possiblePath = 1;
				}else if(data->minimumSteps == nextDistance){
					data->possiblePath++;
				}
			}
			
			// check if the distance is bigger
			if(nextDistance >= *(data_distance + nextColumn + (data->width * nextRow)) && *(data_distance + nextColumn + (data->width * nextRow)) != -1){
				continue;
			}
			
			*(data_distance + nextColumn + (data->width * nextRow)) = nextDistance;
			*(data_move + nextColumn + (data->width * nextRow)) = i;
			shortestPath(data, map, data_move, data_distance, nextRow, nextColumn, nextDistance);
		}
	}
}

void generateMap(data_Map* data, FILE* file){
	// generate map
	char map[data->height][data->width];
		
	for(int i=0; i < data->height; i++){
		for(int j=0; j < data->width; j++){
			fscanf(file, "%c", &map[i][j]);
		}
		
		fgetc(file);
	}

	// find the start and end position
	for(int i = 0; i < data->height;i++){
		for(int j =0; j < data->width;j++){
			if(map[i][j] == 'X') {
				data->endPosition[0] = i;
				data->endPosition[1] = j;
			}else if( map[i][j] == '0'){
				data->startPosition[0] = i;
				data->startPosition[1] = j;
			}
		}
	}

	// make 2d arrays 
	int data_move[data->height][data->width];
	
	for(int i=0; i<data->height;i++) {
		for(int j=0; j<data->width; j++) {
			data_move[i][j]= -1;
		}
	}
	
	int data_distance[data->height][data->width];
	
	for(int i=0; i < data->height;i++){
		for(int j =0; j < data->width;j++){
			data_distance[i][j]= -1;
		}
	}
	
	data_distance[data->startPosition[0]][data->startPosition[1]] = 0;

	// find the steps and path
	data->minimumSteps = -1;
	data->possiblePath = 0;
	shortestPath(data, &map[0][0], &data_move[0][0], &data_distance[0][0], data->startPosition[0], data->startPosition[1], 0);
	int row = data->endPosition[0];
	int column = data->endPosition[1];
	
	int reverseMoves[4][2] = {
		{1,0}, // down from up
		{0,-1}, // left from righ
		{-1, 0}, // up from down
		{0, 1}, // right from left
	};

	// shape of the path
	while(1) { 
		if(row == data->startPosition[0] && column == data->startPosition[1]){
			break;
		}
		
		if(map[row][column] != 'X'){
			map[row][column] = '.';
		}
		
		int next = data_move[row][column];
		row += reverseMoves[next][0];
		column += reverseMoves[next][1];
	}

	// save the path in data holder
	char temp[fileMapLength];
	strcpy(temp, dataHolder);
	strcpy(data->newPath, strcat(temp, data->fileName));
	FILE* savefile = fopen(data->newPath, "w");
	
	for(int i=0; i < data->height; i++){
		for(int j =0; j < data->width; j++) {
			fprintf(savefile, "%c", map[i][j]);
		}
		
		fprintf(savefile, "\n");
	}
	
	fclose(savefile);

	rewind(file);
}

void WidthHeight(data_Map* data, FILE* file){
	char temp[widthMap + 1];
	fgets(temp, widthMap + 1, file);
	int height = 1;
	
	for(; !feof(file); height++){
		fgets(temp, widthMap + 1, file);
	}
	
	data->width = strlen(temp);
	data->height = height;
	rewind(file);
}

data_Map inputData(){ // input data file
	data_Map data;
	char fileName1[fileMapLength];
	char temp[fileMapLength];
	
	while(1) {
		system("cls");
		printf("Input File Name : ");
		scanf("%s", fileName1); getchar();
		
		int special = 1;
		
		for(int i =0; i<newPathCount;i++){
			if(strcmp(newPathData[i].fileName, fileName1) == 0){
				special = 0;
			}
		}
			
		if(special){
			if(strstr(fileName1,".dig")){
				break;
			} 
			
			if(strcmp(fileName1, "Exit") == 0){
				strcpy(data.fileName, "None");
				return data;
			}else{
				printf("Must be a .dig file extension!\nPress enter!\n");
				getchar(); getchar();
			}
		}else{
			printf("%s is already in data\nPress enter!\n", fileName1);
			getchar(); getchar();
		}
	}

	strcpy(data.fileName, fileName1);
	strcpy(temp, fileMap);
	strcpy(data.fileLocation, strcat(temp, fileName1));

	FILE* file = fopen(data.fileLocation, "r");
	WidthHeight(&data, file);
	generateMap(&data,file);

	fclose(file);
	return data;
}

void printFile_Map(data_Map map){
	char temp[widthMap];
	FILE* file =  fopen(map.newPath, "r");
	for(int i=0; i<map.height; i++) {
		fgets(temp, widthMap, file);
		printf("%s", temp);
	}
	
	fclose(file);
}

void printData(data_Map data){
	printf("File Name: %s\n", data.fileName);
	printf("File Location: %s\n", data.fileLocation);
	printf("Height & Width: %d & %d\n", data.height, data.width);
	printf("Minimum Steps: %d\n", data.minimumSteps);
	printf("Number Of Posibble Path: %d\n", data.possiblePath);
}

// Show Discovered Map List
void showMapList(){
	int chooseMap;
	system("cls");
	printf("=====SHOW DISCOVERED MAP LIST=====\n\n\n");
	
	for(int i=0; i < newPathCount; i++){
		printf("%d. %s\n", i+1, newPathData[i].fileName);
	}
	
	printf("%d. Exit\n", newPathCount + 1);
	printf("\nPlease select a map: ");
	scanf("%d", &chooseMap); getchar();
	chooseMap--;
	
	if(chooseMap == newPathCount + 1){
		return;
	} 
	
	// printing map
	system("cls");
	printf("---- %s ----\n", newPathData[chooseMap].fileName);
	printFile_Map(newPathData[chooseMap]);
	printData(newPathData[chooseMap]);
	printf("\nPress Enter!");
	getchar(); getchar(); 
}

// Exit and Save Progress
void exitSave(){
	FILE* file = fopen(mapList, "w");
	fprintf(file, "%d\n", newPathCount);
	
	for(int i =0; i < newPathCount;i++){
		fprintf(file, "%s\n", newPathData[i].fileName);
		fprintf(file, "%s\n", newPathData[i].fileLocation);
		fprintf(file, "%s\n", newPathData[i].newPath);
		fprintf(file, "%d\n", newPathData[i].minimumSteps);
		fprintf(file, "%d\n", newPathData[i].possiblePath);
		fprintf(file, "%d\n", newPathData[i].width);
		fprintf(file, "%d\n", newPathData[i].height);
		fprintf(file, "%d %d\n", newPathData[i].startPosition[0], newPathData[i].startPosition[1]);
		fprintf(file, "%d %d\n", newPathData[i].endPosition[0], newPathData[i].endPosition[1]);
	}
		
	fclose(file);
}

//MAIN MENU
void mainMenu(){
	
	int choice = 3;
	int exit = 0;
	data_Map temp;			

		while(!exit) { // while not exit
		system("cls");
		printf("-------------------------------------\n");
		printf("------WELCOME TO MINER'S GUILD------\n");
		printf("-------------------------------------\n\n");
		
		printf(" ===== MAIN MENU ====="
				"\n1)Show Discovered Map List\n"
				"2)Discover New Map\n"
				"3)Exit & Save Progress\n\n");
				
		printf("Enter your choice in numbers : \n");
		scanf("%d", &choice); getchar();
		switch(choice) {
			case 1:
				showMapList();
				break;
			case 2:
				temp = inputData();
				if(strcmp(temp.fileName, "None") == 0) {
					break;
				}else{
					newPathData[newPathCount] = temp;
					newPathCount++;
				}
				break;
			case 3:
				exitSave();
				exit = 1;
				break;
			default:
				printf("\nPlease enter your choice in numbers from the main menu list!\n");
				getchar();
				break;
		}
	}
}

int main(){
	
	FILE* file = fopen(mapList, "r");
	fscanf(file, "%d", &newPathCount);
	for(int i =0; i < newPathCount;i++) {
		fscanf(file, "%s\n", newPathData[i].fileName);
		fscanf(file, "%s\n", newPathData[i].fileLocation);
		fscanf(file, "%s\n", newPathData[i].newPath);
		fscanf(file, "%d\n", &newPathData[i].minimumSteps);
		fscanf(file, "%d\n", &newPathData[i].possiblePath);
		fscanf(file, "%d\n", &newPathData[i].width);
		fscanf(file, "%d\n", &newPathData[i].height);
		fscanf(file, "%d %d\n", &newPathData[i].startPosition[0], &newPathData[i].startPosition[1]);
		fscanf(file, "%d %d\n", &newPathData[i].endPosition[0], &newPathData[i].endPosition[1]);
	}	
	
	fclose(file);
	
	mainMenu();
	
	return 0;
}

void printMap(data_Map data, int* array, const char* name){
	printf("--- %s ---\n" , name);
	
	for(int i=0; i<data.height; i++){
		for(int j=0 ; j<data.width; j++){
			printf("%d\t", * (array + j + data.width * i));
		}
		
		printf("\n");
	}
}
