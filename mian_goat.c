#include<stdio.h>
#include<gtk/gtk.h>
#include<time.h>
#include<stdlib.h>

#define SWAP(x,y,t) ( (t) = (x),(x) = (y),(y) = (t) )
#define MAX 100000

//T-C: time complexity
//using CLOCKS_PER_SEC and we are able to get an accurate number to describe T-C
int dec,sign = 0;

int NUM[MAX];
int SORT[6][MAX];

void destroy(GtkWidget* Widget,gpointer data)
{
	//Exit
	gtk_main_quit();
}

int comp(const void *p,const void *q )
{
	return ( *(int *)p - *(int *)q );
}

void init()
{
	int i=0;
	srand(time(NULL));
	for(;i<=MAX-1;i++)
	{
		NUM[i] = rand();
		SORT[0][i] = NUM[i];
		SORT[1][i] = NUM[i];
		SORT[2][i] = NUM[i];
		SORT[3][i] = NUM[i];
		SORT[4][i] = NUM[i];
		SORT[5][i] = NUM[i];
	}
}

//SWAPSORT ,calculate the worst time complexity is O(n^2) 
double swapsort(int a[],int n)
{
	double time;
	int i,j,min,temp;
	clock_t start,finish;//use count
	start = clock();
	//main_body
	for(i=0; i<n-1; i++)
	{		min = i;
		for(j=i+1; j<n; j++)
		{
			if(a[j] < a[min])
			{
				min = j; 
			}	}
				SWAP(a[j],a[min],temp);
	}		
	finish = clock();
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	return time;
}

void adjust(int a[],int root,int n)
{
	int child,rootkey;
	int temp;
	temp = a[root];
	rootkey = a[root];
  	child = 2 * root;	
	while(child <= n)
	{
	if(child<n && a[child]<a[child+1])
	{
		child += 1;
	}
	if(rootkey > a[child])
	{
		break;
	}
	else{
		a[child/2] = a[child];
		child *= 2;
	}
	}
	a[child/2] = temp;
}
double heapsort(int a[],int n)
{
	int i,j;
	int temp;
	double time;
	clock_t start,finish;
	start = clock();
	for(i=n/2;i>0;i--)
		adjust(a,i,n);
	for(i = n-1; i >0; i--)
		SWAP(a[1],a[i+1],temp);
		adjust(a,1,i);
	finish = clock();
	time = (double)(finish-start)/CLOCKS_PER_SEC;
	return time;
}

double insertsort(int a[],int n)
{
	int i,j,next;
	double time;
	clock_t start,finish;
	start = clock();
	//main body
	for(i=1; i<n; i++)
	{
		next = a[i];
		for(j=i-1; j>=0 && next<a[j]; j--)
		{
			a[j+1]=a[j];
		}
		a[j+1] = next;
	}
	finish = clock();
	time = (double)(finish-start)/CLOCKS_PER_SEC;
	return time;
}

//POPSORT worst time-complexity is O(n^2) and average T-C is O(n^2)
double popsort(int a[],int n)
{
	double time;
	int i,j,temp; 
	clock_t start,finish;
	start = clock();
	//main_body
	for(i=0;i<n-1;i++)
		for(j=0;j<n-i-1;j++)
			if(a[j]>a[j+1])
				SWAP(a[j],a[j+1],temp);
	finish = clock();
	time = (double)(finish - start)/CLOCKS_PER_SEC;
	//printf("pop%lf",time);
	return time;
}

void merge(int list[],int sort[],int i,int m,int n)
{
	int j,k,t;
	j = m+1; k = i;//index position
	while(i<=m && j<=n)
	{
		if(list[i]<=list[j])
			sort[k++] = list[i++];
		else
			sort[k++] = list[j++];
	}
	if(i > m)
		for(t=j;t<=n;t++)
			sort[k+t-j] = list[t];
	else
		for(t=i;t<=m;t++)
			sort[k+t-i] = list[t];
}

void merge_pass(int list[],int sort[],int n,int length)
{
	int i,j;
	for(i=0;i<=n-2*length;i+=2*length)
		merge(list,sort,i,i+length-1,i+2*length-1);
	if(i+length < n)
		merge(list,sort,i,i+length-1,n-1);
	else
		for(j=i;j<n;j++)
			sort[j] = list[j];
}

double mergesort(int list[],int n)
{
	int length = 1;
	double time;
	int extra[MAX];
	clock_t start,finish;
	start = clock();
	while(length<n)
	{
	merge_pass(list,extra,n,length);
	length *= 2;
	merge_pass(extra,list,n,length);
	length *= 2;
	}
	finish = clock();
	time = (double)(finish-start)/CLOCKS_PER_SEC;
	return time;
}	
//FASTSORT worst T-C is O(n^2) and average T-C is O(nlogn)
//qsort() is a fun belong to standard-lib
double quicksort(int a[],int n)
{
	const char TIME[20];
	double time;
	clock_t start,finish;
	start = clock();
	qsort(a,n,sizeof(int),comp);
	finish = clock();
    time = (double)(finish - start)/CLOCKS_PER_SEC;
	//printf("  quick%lf",time);
	return time;
}

void sort(GtkWidget** entry)
{
	char number[6][15];
	double a;
	a = popsort(SORT[0],MAX);
	sprintf(number[0],"%lf",a);
	a = quicksort(SORT[1],MAX);
	sprintf(number[1],"%lf",a);
	a = mergesort(SORT[2],MAX);
	sprintf(number[2],"%lf",a);
	a = heapsort(SORT[3],MAX);
	sprintf(number[3],"%lf",a);
	a = insertsort(SORT[4],MAX);
	sprintf(number[4],"%lf",a);
	a = insertsort(SORT[5],MAX);
	sprintf(number[5],"%lf",a);
	
	gtk_entry_set_text(GTK_ENTRY(*(entry)),number[0]);
	gtk_entry_set_text(GTK_ENTRY(*(entry+1)),number[1]);
	gtk_entry_set_text(GTK_ENTRY(*(entry+2)),number[2]);
	gtk_entry_set_text(GTK_ENTRY(*(entry+3)),number[3]);
	gtk_entry_set_text(GTK_ENTRY(*(entry+4)),number[4]);
	gtk_entry_set_text(GTK_ENTRY(*(entry+5)),number[5]);
	//number[1] = popsort(SORT[0],MAX);
	//printf("%s",number[1]);

}


//Interface
int main(int argc,char* argv[])
{
	//loop vairable
	int i = 0;
	gtk_init(&argc,&argv);
	GtkWidget* father_window;
	//init data
	GtkWidget* button_create_data;
	//sort
	GtkWidget* button_sort;
	//sort label to identify
	GtkWidget* Label[6];
	Label[0] = gtk_label_new("PopSort");
	Label[1] = gtk_label_new("QuickSort");
	Label[2] = gtk_label_new("MergeSort");
	Label[3] = gtk_label_new("HeapSort");
	Label[4] = gtk_label_new("InsertSort");
	Label[5] = gtk_label_new("SwapSort");
	GtkWidget* box_ver[3];
	GtkWidget* box_hor[2];
	GtkWidget* Entry[6];
	for(;i<=5;i++)
		Entry[i] = gtk_entry_new();
	//create some box as container
	for(i=0;i<=1;i++)
		{
			box_ver[i] = gtk_vbox_new(FALSE,0);
			box_hor[i] = gtk_hbox_new(FALSE,0);
		}
	box_ver[2] = gtk_vbox_new(FALSE,0);
	//
	father_window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_container_set_border_width( GTK_CONTAINER(father_window), 10 );
	//create Button-Groups with labels
	button_create_data = gtk_button_new_with_label("Init All Data");
	button_sort = gtk_button_new_with_label("Test Time Complexity");
	//add a ver_box on the father window and pack other box in box_ver[0]
	gtk_container_add(GTK_CONTAINER(father_window),box_ver[0]);
	gtk_box_pack_start(GTK_BOX(box_ver[0]),box_hor[0],TRUE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(box_ver[0]),box_hor[1],TRUE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(box_hor[0]),box_ver[1],TRUE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(box_hor[0]),box_ver[2],TRUE,TRUE,5);
	for(i=0;i<=5;i++)
	{
		gtk_box_pack_start(GTK_BOX(box_ver[1]),Label[i],TRUE,TRUE,5);
		gtk_box_pack_start(GTK_BOX(box_ver[2]),Entry[i],TRUE,TRUE,5);
		gtk_editable_set_editable(G_OBJECT(Entry[i]),TRUE);
	}
	//pack buttons in the box
	gtk_box_pack_start(GTK_BOX(box_hor[1]),button_create_data,TRUE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(box_hor[1]),button_sort,TRUE,TRUE,5);
	//gtk_box_pack_start(box1,button_create_data,FALSE,padding);
	g_signal_connect(G_OBJECT(father_window),"delete_event",G_CALLBACK(destroy),NULL);
	//callback init_data()
    //g_signal_connect(G_OBJECT(father_window),"destroy",G_CALLBACK(destroy),NULL);
	g_signal_connect(G_OBJECT(button_create_data),"clicked",G_CALLBACK(init),NULL);
	g_signal_connect_swapped(G_OBJECT(button_sort),"clicked",G_CALLBACK(sort),Entry);
	gtk_widget_show_all(father_window);
	gtk_main();	
	return 0;
}
