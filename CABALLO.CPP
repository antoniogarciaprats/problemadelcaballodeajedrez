#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <dos.h>

#define NORMAL LIGHTGRAY
#define INVERSO LIGHTGRAY*16
#define MARCADO GREEN
#define ACOSADO RED+BLINK
#define MINIMO BLUE

/************************************************************/
/******************  rutinas de apoyo   *********************/
/************************************************************/

void esperatecla() {

	char c;
	while (!kbhit());
	c=getch();
}

void writetodo(int t[8][8]) {

	int i,j;

	for (i=0;i<8;i++) {
		gotoxy(1,i+1);
		for (j=0;j<8;j++)
			cprintf("%d  ",t[i][j]);
	}
}

void writeuno(int t[8][8],int m, int n,int color) {

	textattr(color);
	gotoxy(m*3+1,n+1);
	cprintf("%d",t[m][n]);
	textattr(7);
}

void writeacosados(int t[8][8], int m, int n,int color) {

	m-=2;
	n-=1;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
	n+=2;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
	m++;
	n++;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
	m+=2;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
	m++;n--;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
	n-=2;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
	m--;n--;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
	m-=2;
	if (m>=0 && m<8 && n>=0 && n<8)
		if (t[m][n]==0) writeuno(t,m,n,color);
}


/************************************************************/
/******************     problema        *********************/
/************************************************************/

int solucion(int restantes) {

	return(restantes==0?1:0);
}

int factible(int t[8][8], int m, int n) {

	return(t[m][n]==0);
}

int cuenta_acosos(int t[8][8], int m, int n) {

	int r=0,x=m,y=n;

	m-=2;
	n-=1;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;
	n+=2;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;
	m++;
	n++;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;
	m+=2;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;
	m++;n--;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;
	n-=2;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;
	m--;n--;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;
	m-=2;
	if (m>=0 && m<8 && n>=0 && n<8) if (t[m][n]==0) r++;

	/*   feed back  */
	writeacosados(t,x,y,ACOSADO);
	gotoxy(5,10);
	cprintf("acosa a %d",r);
	esperatecla();
	writeacosados(t,x,y,NORMAL);
	gotoxy(25,4);
	clreol();

	return(r);
}

void select_f(int t[8][8], int *m, int *n) {
	int i=-1,j=-1,x=*m,y=*n;
	int max=9;
	int temp;
	char c;

	writeuno(t,*m,*n,INVERSO);	/* feed back */
	esperatecla();
	(*m)-=2;
	(*n)--;

	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
			max=temp;
		 }
		 else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	(*n)+=2;
	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,i,j,NORMAL);	/* feed back */
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
			max=temp;
		}
		else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	(*m)++;
	(*n)++;
	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,i,j,NORMAL);	/* feed back */
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
			max=temp;
		}
		else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	(*m)+=2;
	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,i,j,NORMAL);	/* feed back */
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
			max=temp;
		}
		else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	(*m)++;
	(*n)--;
	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,i,j,NORMAL);	/* feed back */
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
			max=temp;
		}
		else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	(*n)-=2;
	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,i,j,NORMAL);	/* feed back */
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
			max=temp;
		}
		else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	(*m)--;
	(*n)--;
	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,i,j,NORMAL);	/* feed back */
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
			max=temp;
		}
		else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	(*m)-=2;
	if (*m>=0 && *m<8 && *n>=0 && *n<8) {
		writeuno(t,*m,*n,MARCADO);	/* feed back */
		if (factible(t,*m,*n) && (temp=cuenta_acosos(t,*m,*n))<max) {
			writeuno(t,i,j,NORMAL);	/* feed back */
			writeuno(t,*m,*n,MINIMO);	/* feed back */
			i=*m;
			j=*n;
		}
		else writeuno(t,*m,*n,NORMAL);	/* feed back */
	}
	if (i==-1) {
		printf("no encuentro la solucion");
		exit(1);
	}
	writeuno(t,x,y,NORMAL);	/* feed back */
	*m=i;
	*n=j;
}

void caballo(int t[8][8], int m, int n) {
	int i,j;
	int restantes=63;  /* casillas que quedan por visitar */

	for (i=0;i<8;i++)
		for (j=0;j<8;j++)	/* casilla==0 candidato no visitado */
			t[i][j]=0;	/* casilla==1 candidato ya visitado */

	writetodo(t);			/* feed back */

	t[m][n]=1;			/* comenzamos en la casilla 1,1 */

	writeuno(t,m,n,NORMAL);		/* feed back */

	while (!solucion(restantes)) {
		select_f(t,&m,&n);
		restantes-=1;
		t[m][n]=1;
		writeuno(t,m,n,NORMAL);	/* feed back */
	}

	/* feed back */
	gotoxy(1,9);
	if (restantes==0) cprintf("soluci¢n encontrada.\n");
	else cprintf("no hay soluci¢n.\n");
}

void main (void) {

	int t[8][8];

	clrscr();

	gotoxy(20,25);
	textattr(NORMAL); cprintf("NORMAL ");
	textattr(INVERSO); cprintf("ACTUAL");
	textattr(NORMAL); cprintf(" ");
	textattr(MARCADO); cprintf("CALCULANDO ACOSO");
	textattr(NORMAL); cprintf(" ");
	textattr(ACOSADO); cprintf("ACOSADO");
	textattr(NORMAL);

	caballo(t,0,0);
	while (!kbhit());
}

