
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10

typedef struct{
    char fname[50];
    char lname[50];
    char middleInitial;
}name;

typedef struct{
    name studentName;
    int idNum;
    int studentGrades[3];
}studentDetail;

typedef struct{
    studentDetail student[MAX];
    int count;
}classRecord;

typedef struct{
    classRecord classList;
    classRecord examRetake[3];
    classRecord examRanking[3];
}classResults;

studentDetail addStudent();
void populateStudents(classRecord *class);
void checkExams(classResults *results);
classRecord getRetakers(classRecord list, int examNum);
void rankStudents(classResults *);
classRecord getRankers(classRecord L, int examNum);


void displayStudent(studentDetail S);
void displayClass(classRecord L);
void searchStudByName();
void deleteStudent(classRecord L, int id);
void insertFirst(classRecord L, studentDetail S);
void insertMiddle(classRecord L, studentDetail S);
void insertLast(classRecord L, studentDetail S);

/* 
1. a function that searches student by a name and is case insensitive, 
and displays all the student with the same nanmes

2. a function that deletes that student from the classlist

3. A function that inserts a student to a list (first,middle,last)

4. A function that displays a student
*/



void displayClass(classRecord L){
    int i, count = L.count;
    if(count == 0){
    	printf("There are currently no students in the class.\n");
	}else{
		for(i=0;i<count;i++){
        displayStudent(L.student[i]);
    	}
	}
    
}

void displayStudent(studentDetail S){
    printf("ID: %d\n", S.idNum);
    printf("Name: %s %s %s\n", S.studentName.fname, S.studentName.middleInitial, S.studentName.lname);
}

int main(void){
    classResults result;
    int exit = 1;
    
    result.classList.count = 0;
    result.examRetake[0].count = 0;
    result.examRetake[1].count = 0;
    result.examRetake[2].count = 0;
    
    result.examRanking[0].count = 0;
    result.examRanking[1].count = 0;
    result.examRanking[2].count = 0;
    
    int choice;
    while(exit){
        printf("Classroom of the Elite: Class D Student Database\n");
        printf("1. Add a student\n");
        printf("2. Display all students\n");
        printf("3. Check Exams\n");
        printf("4. Rank Students\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            // add a student
            if(result.classList.count <= 10){
                populateStudents(&result.classList);
            }else{
                printf("Maximum Number of Students per Class is only 10");
            }
        }else if(choice == 2){
            displayClass(result.classList);
        }else if(choice == 3){
            checkExams(&result);
        }else if(choice == 4){
            rankStudents(&result);
        }else if(choice == 5){
            exit = 0;
        }else{
            printf("Invalid choice selected.\n");
        }
        printf("\n");
    }
}

void populateStudents(classRecord *class){
    // code here
    printf("===STUDENT INFORMATION===\n \n");
    class->student[class->count++] = addStudent();
}

studentDetail addStudent(){
    studentDetail student;
    printf("Input First Name: ");
    scanf("%s", &student.studentName.fname);
    getchar();
    printf("Input Last Name: ");
    scanf("%s", &student.studentName.lname);
    getchar();
    printf("Input Middle Initial: ");
    scanf("%c", &student.studentName.middleInitial);
    printf("Input ID Number: ");
    scanf("%d", &student.idNum);
    printf("Input Exam Score 1: ");
    scanf("%d", &(student.studentGrades[0]));
    printf("Input Exam Score 2: ");
    scanf("%d", &(student.studentGrades[1]));
    printf("Input Exam Score 3: ");
    scanf("%d", &(student.studentGrades[2]));
    return student;
}

classRecord getRankers(classRecord L, int examNum){
	studentDetail temp;
	int i, j, min;
	for(i=0;i<L.count;i++){
		min = i;
		for(j=i+1;j<L.count;j++){
			if(L.student[j].studentGrades[examNum] < L.student[min].studentGrades[examNum]){
				min = j;
			}
		}
		temp = L.student[min];
		L.student[min] = L.student[i];
		L.student[i] = temp;
	}
	return L;
}

void rankStudents(classResults *R){
	int i, j, rank = 1, studCount;
	printf("\n===EXAM RANKINGS===\n");
	for(i=0;i<3;i++){
		R->examRanking[i] = getRankers(R->classList, i);
		studCount = R->examRanking[i].count;
		printf("Exam %d: \n", i+1);
		for(j=studCount-1;j>=0;j--){
			printf("%d - %s\n", rank, R->examRanking[i].student[j].studentName.fname);
			rank++;
		}
		rank = 1;
	}
}

void checkExams(classResults *results){
    int i,j,k, count = results->classList.count;
    for(i=0;i<count;i++){
        results->examRetake[i] = getRetakers(results->classList, i);
    }
    for(i=0;i<3;i++){
        printf("Retakers Needed for Exam %d: ", i+1);
        if(results->examRetake[i].count == results->classList.count){
            printf("All Students Have to Retake Exam\n");
        }else if(results->examRetake[i].count > 0){
            for(j=0;j<results->examRetake[i].count;j++){
                printf("%s ", results->examRetake[i].student[j].studentName.fname);
            }
            printf("\n");
        }else{
            printf("No Retakers for Exam %d\n", i+1);
        }
    }
}

classRecord getRetakers(classRecord list, int examNum){
    int i,j;
    classRecord newList;
    newList.count = 0;
    for(i=0, j=0;i<list.count;i++){
        if(list.student[i].studentGrades[examNum] < 60){
            newList.student[j++] = list.student[i];
            newList.count++;
        }
    }
    return newList;
}
    

    
