#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define SORT_NO 5
#define MAX 45
#define COLORS 90

int a[MAX];
double cc[COLORS];
char text1[5];
char text2[5];
int swapflag = 0;
int i = 0, j = 0;
int flag = 0;
int dirflag = 0;
int count = 1;
int sorting = 0;
const char *sort_string[] = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Ripple Sort", "Comb Sort"};
int sort_count = 0;
int speed = 10;
int arrayFlag = 1;
int backFlag = 1;
int fastslow = 0;
int vertical_index;

double randomFlaot();
void bitmap_output(int, int, const char *, void *);
void makedelay(int);
void display_text();
void frontPage();
void Initialize();
void display();
void int_str(int rad, char r[]);
int notsorted();
void keyboard(unsigned char key, int x, int y);
void ripplesort();
void bubblesort();
void selectionsort();
void insertionsort();
char *whichmode(char k);
void quickSort(int low, int high);
int partition(int low, int high);
void swap(int *a, int *b);
void combSort();
void shellSort();

char* whichmode(const int d)
{
    if (d == 1)
    {
        return "Interactive Mode";
    }
    return "Outstanding Mode";
}

double randomFlaot()
{
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

void bitmap_output(int x, int y, const char *string, void *font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

void int_str(int rad, char r[])
{
    snprintf(r, 10, "%d", rad);
}

void display_text()
{
    glColor3d(cc[36], cc[37], cc[38]);
    bitmap_output(250, 750, "REPRESENTATION OF SORTING AND SEARCHING ALGORITHMS", GLUT_BITMAP_TIMES_ROMAN_24);
    char text[20];
    glColor3d(cc[39], cc[40], cc[41]);
    bitmap_output(15, 700, "This program sorts a random set of integers in ascending order by displaying them graphically", GLUT_BITMAP_HELVETICA_18);
    bitmap_output(15, 680, "as bars with varying height", GLUT_BITMAP_HELVETICA_18);

    glColor3d(cc[42], cc[43], cc[44]);
    int_str(speed, text);
    strcat(text, "ms");

    bitmap_output(600, 510, whichmode(fastslow), GLUT_BITMAP_HELVETICA_18);
    char iff[50] = "swapping ";
    strcat(iff, text1);
    strcat(iff, " and ");
    strcat(iff, text2);

    glBegin(GL_LINE_LOOP);
    glColor3d(cc[42], cc[43], cc[44]);
    glVertex3f(10.0f, 740.0f, 0.0f);
    glColor3d(cc[45], cc[46], cc[47]);
    glVertex3f(690.0f, 740.0f, 0.0f);
    glColor3d(cc[48], cc[49], cc[50]);
    glVertex3f(690.0f, 500.0f, 0.0f);
    glColor3d(cc[51], cc[52], cc[53]);
    glVertex3f(10.0f, 500.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(cc[47], cc[52], cc[10]);
    glVertex2f(450.0, 740.0);
    glColor3d(cc[42], cc[17], cc[74]);
    glVertex2f(450.0, 500.0);
    glEnd();
    glColor3d(cc[56], cc[77], cc[36]);
    bitmap_output(550.0, 700.0, "STEP", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3d(cc[34], cc[58], cc[28]);
    bitmap_output(470, 600, iff, GLUT_BITMAP_HELVETICA_18);

    glColor3d(cc[54], cc[55], cc[56]);
    if (sorting == 0)
    {
        bitmap_output(15, 645, "MENU", GLUT_BITMAP_TIMES_ROMAN_24);
        bitmap_output(15, 625, "Press s to SORT", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 605, "Press c to SELECT the sort algorithm", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 585, "Press r to RANDOMISE", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 565, "Esc to QUIT", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(15, 545, "Selected sort: ", GLUT_BITMAP_HELVETICA_18);
        bitmap_output(80, 545, *(sort_string + sort_count), GLUT_BITMAP_HELVETICA_18);
    }
    else if (sorting == 1)
    {
        glColor3d(cc[57], cc[58], cc[59]);
        bitmap_output(55, 555, "Sorting in progress...", GLUT_BITMAP_HELVETICA_18);
        glColor3d(cc[60], cc[61], cc[62]);
        bitmap_output(55, 535, "Press p to PAUSE", GLUT_BITMAP_HELVETICA_18);
    }
}

void Initialize()
{
    srand(time(0));
    int temp1;

    if (arrayFlag == 1)
    {
        for (temp1 = 0; temp1 < MAX; temp1++)
        {
            a[temp1] = rand() % 100 + 1;
        }
        arrayFlag = 0;
    }

    if (backFlag == 1)
    {
        for (int i = 0; i < COLORS; i++)
        {
            cc[i] = randomFlaot();
        }

        i = j = 0;
        dirflag = 0;
        count = 1;
        flag = 0;
        glClearColor(randomFlaot(), randomFlaot(), randomFlaot(), randomFlaot());
        backFlag = 0;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 699, 0, 799);
}

int notsorted()
{
    int q;
    for (q = 0; q < MAX - 1; q++)
    {
        if (a[q] > a[q + 1])
            return 1;
    }
    return 0;
}

void display()
{
    int ix, temp;
    glClear(GL_COLOR_BUFFER_BIT);


        display_text();
        char text[10];

        for (ix = 0; ix < MAX; ix++)
        {
            glBegin(GL_LINE_LOOP);
            glColor3d(cc[63], cc[64], cc[65]);
            glVertex2f(10 + (700 / (MAX + 1)) * ix, 50);
            glColor3d(cc[66], cc[67], cc[68]);
            glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50);
            glColor3d(cc[69], cc[70], cc[71]);
            glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50 + a[ix] * 4);
            glColor3d(cc[72], cc[73], cc[74]);
            glVertex2f(10 + (700 / (MAX + 1)) * ix, 50 + a[ix] * 4);
            glEnd();

            int_str(a[ix], text);
            glColor3d(cc[75], cc[76], cc[77]);
            bitmap_output(12 + (700 / (MAX + 1)) * ix, 30, text, GLUT_BITMAP_HELVETICA_18);
        }

        if (swapflag == 1 || sorting == 0)
        {
            glBegin(GL_POLYGON);
            glColor3d(cc[75], cc[76], cc[77]);
            glColor3d(cc[78], cc[79], cc[80]);
            glVertex2f(10 + (700 / (MAX + 1)) * vertical_index, 50);
            glColor3d(cc[81], cc[82], cc[83]);
            glVertex2f(10 + (700 / (MAX + 1)) * (vertical_index + 1), 50);
            glColor3d(cc[84], cc[85], cc[86]);
            glVertex2f(10 + (700 / (MAX + 1)) * (vertical_index + 1), 50 + a[vertical_index] * 4);
            glColor3d(cc[87], cc[88], cc[89]);
            glVertex2f(10 + (700 / (MAX + 1)) * vertical_index, 50 + a[vertical_index] * 4);
            glEnd();
            swapflag = 0;
        }
    glFlush();
}

void makedelay(int)
{
    if (sorting)
    {
        switch (sort_count)
        {
        case 0:
            bubblesort();
            break;
        case 1:
            selectionsort();
            break;
        case 2:
            insertionsort();
            break;
        case 3:
            ripplesort();
            break;
        case 4:
            combSort();
            break;
        }
    }
    if (fastslow == 1)
    {
        sorting = 0;
    }
    speed = 1;
    glutPostRedisplay();
    glutTimerFunc(speed, makedelay, 100);
}

void keyboard(unsigned char key, int x, int y)
{
     if (key == 'k')
    {
        speed = 50;
    }
    else if (sorting != 1)
    {
        switch (key)
        {
        case 27:
            exit(0);
        case 's':
            sorting = 1;
            break;
        case 'i':
            fastslow = 1;
            break;
        case 'o':
            fastslow = 0;
            break;
        case 'r':
            arrayFlag = 1;
            Initialize();
            break;
        case 'x':
            backFlag = 1;
            arrayFlag = 0;
            Initialize();
        case 'z':
            arrayFlag = 1;
            backFlag = 1;
            Initialize();
            break;
        case 'c':
            sort_count = (sort_count + 1) % SORT_NO;
            break;
        }
    }
    else if (sorting == 1)
    {
        if (key == 'p')
            sorting = 0;
        speed = 1000;
    }
    else
        Initialize();
}

void insertionsort()
{
    int temp;

    while (i < MAX)
    {
        if (flag == 0)
        {
            j = i;
            flag = 1;
        }
        while (j < MAX - 1)
        {
            if (a[j] > a[j + 1])
            {
                swapflag = 1;
                temp = a[j];
                printf("inside while if ");
                a[j] = a[j + 1];
                a[j + 1] = temp;
                vertical_index = j;

                goto A;
            }
            j++;
            if (j == MAX - 1)
            {
                flag = 0;
            }
            int_str(a[j], text1);
            int_str(a[j + 1], text2);
            printf("swap %d and %d\n", a[j], a[j + 1]);
        }
        i++;
    }
    sorting = 0;
A:
    i = j = 0;
}

void selectionsort()
{
    int temp, j, min, pos;

    while (notsorted())
    {

        while (i < MAX - 1)
        {
            min = a[i + 1];
            pos = i + 1;
            if (i != MAX - 1)
            {
                for (j = i + 2; j < MAX; j++)
                {
                    if (min > a[j])
                    {
                        min = a[j];
                        vertical_index = i;
                        pos = j;
                    }
                }
            }
            printf("\n i=%d min=%d at %d", i, min, pos);
            printf("\n checking %d and %d", min, a[i]);
            if (min < a[i])
            {

                //j=pos;
                int_str(min, text1);
                int_str(a[i], text2);
                printf("\n swapping %d and %d", min, a[i]);
                temp = a[pos];
                a[pos] = a[i];
                a[i] = temp;
                swapflag = 1;
                goto A;
            }
            i++;
        }
    }
    sorting = 0;
    i = j = 0;
A:
    printf("");
}

void bubblesort()
{
    int temp;
    while (notsorted())
    {
        while (j < MAX - 1)
        {
            if (a[j] > a[j + 1])
            {
                swapflag = 1;
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                vertical_index = j + 1;

                int_str(a[j], text1);
                int_str(a[j + 1], text2);
                goto A;
            }
            j++;
            if (j == MAX - 1)
                j = 0;
            printf("swap %d and %d\n", a[j], a[j + 1]);
        }
    }
    sorting = 0;
A:
    printf("");
}

void ripplesort()
{
    int temp;
    while (notsorted() && sorting)
    {
        if (dirflag == 0)
        {
            while (j < MAX - 1)
            {
                if (a[j] > a[j + 1])
                {
                    swapflag = 1;
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    vertical_index = j + 1;
                    goto A;
                }
                j++;
                if (j == MAX - 1)
                {
                    count++;
                    j = MAX - count;
                    dirflag = 1 - dirflag;
                }

                printf("j=%d forward swap %d and %d\n", j, a[j], a[j + 1]);
                int_str(a[j], text1);
                int_str(a[j + 1], text2);
            }
        }
        else
        {
            while (j >= 0)
            {
                if (a[j] > a[j + 1])
                {
                    swapflag = 1;
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    vertical_index = j + 1;
                    goto A;
                }
                j--;
                if (j == 0)
                {
                    dirflag = 1 - dirflag;
                }

                printf("j=%d backward swap %d and %d\n", j, a[j], a[j + 1]);
                int_str(a[j], text1);
                int_str(a[j + 1], text2);
            }
        }
    }
    sorting = 0;
A:
    printf("");
}

int getNextGap(int gap)
{
    gap = (gap * 10) / 13;

    if (gap < 1)
        return 1;
    return gap;
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void combSort()
{
    int gap = MAX;
    bool swapped = true;

    while (notsorted())
    {
        printf("not done");
        while (gap != 1 || swapped == true)
        {
            gap = getNextGap(gap);

            swapped = false;

            for (int j = 0; j < MAX - gap; j++)
            {
                if (a[j] > a[j + gap])
                {
                    swap(&a[j], &a[j + gap]);
                    swapflag = 1;
                    swapped = true;
                    vertical_index = j + gap;

                    int_str(a[j], text1);
                    int_str(a[j + gap], text2);

                    goto A;
                }
            }
        }
    }
    sorting = 0;

A:
    printf("");
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(2000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Representation of sorting and searching algorithms using openGL");
    Initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, makedelay, 1);
    glutMainLoop();
}
