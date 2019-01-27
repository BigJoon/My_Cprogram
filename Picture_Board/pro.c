#include <stdio.h>
#include <stdlib.h>

void Swap(char*a, char*b);
char**Rotate_90(int*height, int*width, char**img);
char** AllocateImage(int height, int width);
void DeallocateImage(char** img, int height, int width);
void PrintImage(char**img, int height, int width);
char **Resize(int arg1, int*height, int*width, char **img);
char **Rotate(int*height, int*width, char**img, int angle);
void Flip(int*height, int*width, int flag, char**img); 
char* Copy(int x1, int y1, int c_h, int c_w, int height, int width, char**img,int x2,int y2);
void Paste(int x2, int y2, int height, int width, char**img, char*tmp);
void Fill(char**img, int h, int w, int x, int y, char color);
void Fill_ex(char**img, int h, int w, int x, int y, char color);
void Fill_Count(char**img, int h, int w, char color, int *pixel);
//start main.
int main(void)
{
	int h, w; // variables for height and width
	char **img;//for image.
	int i, j, k;
	int test_case;
	int arg1;
	int q_num,r_num;//for get query number
	int angle,flag;
	int x1, y1, c_h, c_w, x2, y2;
	char * tmp;
	int x, y;
	int pixel = 0;
	char color;

	while (1)
	{
		printf("Input testcase : ");
		scanf("%d", &test_case);
		if (test_case > 0)
			break;
		else
		{
			printf("Testcase must be plus value!!\n");
			continue;
		}
	}


	printf("Input height , width : ");
	scanf("%d %d", &h, &w);
//	if(h<0 || w < 0 )


	if (h> 4096 || w >4096 || h<0 || w<0)
	{
		printf("Size Error\n");
		while (test_case-- > 0)
		{
			printf("Input height , width : ");
			scanf("%d %d", &h, &w);
			if (h <= 4096 && w <= 4096 && h>0 && w>0)
				break;
			else
				printf("Size Error\n");
			
			if (test_case == 1)
				return 0;//if test_case become 1 exit program because it used all possible test_case.
		}
	}
	
	// allocate memory for img matrix.
	img = AllocateImage(h, w);

	printf("Input the image :\n");

	getchar(); // remove enter.

	//Get Image by stdin.
	for (i = 0; i < h; ++i)
	{
		for (j = 0; j < w; ++j)
			*(*(img + i) + j) = getchar();
		getchar(); // remove enter.
	}
	
	while(test_case-- > 0)
	{
		printf("Input number of query : ");
		scanf("%d", &q_num);
		
		//if invalid oreder is put, print Error message and get other query.
		if (!(q_num == 1 || q_num == 2 || q_num == 3 || q_num == 4 || q_num == 5))
		{
			printf("Invalic query Number.\n");
			continue;
		}			

		switch (q_num)
		{
		case 1:
			printf("\nResize\nInput 0 or 1 : ");
			scanf("%d", &arg1);

			//For user who put wrong value in arg1.
			if (!(arg1 == 1 || arg1 == 0))
			{
				printf("U Put wrong Value. Try again~\n");
				break;
			}
			if((h==1 || w==1)&&(arg1 ==1) )
			{
				printf("Size Error\n");
				break;
			}
			img = Resize(arg1, &h, &w, img);
			PrintImage(img, h, w);
			break;
		case 2:
			printf("\nRotate\nInput 0 or 1 or 2 : ");
			scanf("%d", &angle);

			//For user who put wrong value in angle.
			if (!(angle == 0 || angle == 1 || angle == 2))
			{
				printf("U put wrong Value,Try againg~ TT\n");
				break;
			}
			img = Rotate(&h, &w, img, angle);
			PrintImage(img, h, w);
			break;
		case 3:
			printf("\nFlip\nInput 0 or 1 : ");
			scanf("%d", &flag);

			//For user who put wrong value in flag.
			if (!(flag == 0 || flag == 1))
			{
				printf("Hey~ Wrong! Try again!\n");
				break;
			}
			Flip(&h, &w, flag, img);
			PrintImage(img, h, w);
			break;
		case 4:
			printf("\nCopy and Paste\nx1, y1, c_h, c_w, x2, y2 : ");
			scanf("%d %d %d %d %d %d", &x1, &y1, &c_h, &c_w, &x2, &y2);

			//For user who put wrong value in variables. In fact... for prevent Segmentation error.
			if((x1 + c_h) > w || (y1 + c_w) > h || x1<0 || y1<0 || x2<0 || y2<0)
			{
				printf("Error!! Put other query!!\n");
				break;
			}
			if (c_h <= 0 || c_w <= 0)
			{
				printf("Error! copy height or width can't be minus value!!\n");
				break;
			}
			tmp = Copy(x1, y1, c_h, c_w, h, w, img,x2,y2);
			Paste(x2, y2, h, w, img, tmp);
			PrintImage(img, h, w);
			break;
		case 5:
			printf("\nFill\nInput x, y, color : ");
			scanf("%d %d %c", &x, &y, &color);

			////For user who put wrong value in variables.
			if (x > w-1 || y > h-1)
			{
				printf("Error! DO it again!\n");
				break;
			}
			Fill_ex(img, h, w, x, y, color);
			Fill_Count(img,h,w,color,&pixel);
			printf("Number of colored pixels = %d\n", pixel);
			PrintImage(img, h, w);
			break;
		}
	}
	DeallocateImage(img, h, w);
	return 0;
}//End of main.

//printing Img array
void PrintImage(char**img, int height, int width)
{
	int i, j;
	printf("Result Image\n\n");
	for (i = 0;i < height;i++)
	{
		for (j = 0; j < width;j++)
			printf("%c", *(*(img + i) + j));
		printf("\n");
	}
}
//it allocate memory.
char** AllocateImage(int height, int width)
{
	int i;
	char **img;

	img = (char**) malloc(sizeof(char*) * height);
	for (i = 0;i < height;i++)
		*(img + i) = (char*) malloc(sizeof(char) * width);

	return img;
}
//it free memory.
void DeallocateImage(char** img, int height, int width)
{
	int i;

	for (i = 0; i < height; i++)
		free(*(img + i));
	free(img);
}
//copying original array to copy array.
void CopyImage(char** dest, char** src, int height, int width)
{
	int i, j;

	for (i = 0;i < height;i++)
		for (j = 0;j < width;j++)
			*(*(dest + i) + j) = *(*(src + i) + j);
}
//we can reallocate array so..it means we can change size of img array.
char** ReallocateImage(char**img, int*height, int*width, int newHeight, int newWidth)
{
	int i, j;

	if (*height < newHeight)
	{
		img = (char**)realloc(img, sizeof(char*)*(newHeight));
		for (i = 0; i < *height;i++)
			*(img + i) = (char*)realloc(*(img + i), sizeof(char)*(newWidth));
		for (i = *height; i < (newHeight); i++)
			*(img + i) = (char*)malloc(sizeof(char)*(newWidth));
	}
	else
	{
		for (i = *height;i < newHeight;i++)
			free(*(img + i));
		img = (char**)realloc(img, sizeof(char*)*(newHeight));
		for (i = 0;i < newHeight;i++)
		*(img + i) = (char*)realloc(*(img + i), sizeof(char)*(newWidth));
	}
	*height = newHeight;
	*width = newWidth;
	return img;
}
//Resize function double up or down.
char**Resize(int arg1, int*height, int*width, char**img)
{
	int i, j, k;
	char **copy;
	int oldHeight, oldWidth;

	oldHeight = *height;
	oldWidth = *width;

	copy = AllocateImage(oldHeight, oldWidth);
	CopyImage(copy, img, oldHeight, oldWidth);

	//double up size function
	if (arg1 == 0)
	{
		if (*height*2 > 4096 || *width*2  > 4096)
		{
			printf("Size Error\n");
			return 0;
		}

		printf("Result, resize height : %d, width : %d \n", *height*2, *width*2);
		img = ReallocateImage(img, height, width, 2 * (*height), 2 * (*width));

		for (i = 0; i < *height; i++)
			for (j = 0; j < *width ; j++)
				*(*(img + i) + j) = *(*(copy + i / 2) + j / 2);
	}
	//double down size function.
	else if (arg1 == 1)
	{
		img = ReallocateImage(img, height, width, (*height / 2), (*width / 2));

		for (i = 0; i < *height;i++)
		{
			for (j = 0;j< *width; j++)
			{
				*(*(img + i) + j) = (*(*(copy + i * 2) + j * 2) + *(*(copy + i * 2 + 1) + j * 2) + *(*(copy + i * 2) + j * 2 + 1) + *(*(copy + i * 2 + 1) + j * 2 + 1)) / 4;
			
			}
		}
	}

	DeallocateImage(copy, oldHeight, oldWidth);
	return img;
}
//rotate 90 angle.
char**Rotate_90(int*height, int*width, char**img) 
{
	int i, j;
	int oldHeight, oldWidth;
	int tmp; // for swap height and width.
	char **copy;
	oldHeight = *height;
	oldWidth = *width;

	copy = AllocateImage(oldHeight, oldWidth);
	CopyImage(copy, img, oldHeight, oldWidth);

	img = ReallocateImage(img, height, width, oldWidth, oldHeight);
	for (i = 0;i < oldHeight;i++)
	{
		for (j = 0;j < oldWidth;j++)
			*(*(img + j) + oldHeight - i-1) = *(*(copy + i) + j);
	}

	DeallocateImage(copy, oldHeight, oldWidth);
	return img;
}
//Just call Rotate_90 by angle number 0,1,2
char **Rotate(int*height, int*width, char**img, int angle)
{	
		
	switch (angle)
	{
	case 0:
		img = Rotate_90(height, width, img);
		break;
	case 1:
		img = Rotate_90(height, width, img);
		img = Rotate_90(height, width, img);
		break;
	case 2:
		img = Rotate_90(height, width, img);
		img = Rotate_90(height, width, img);
		img = Rotate_90(height, width, img);
		break;
	}	
	return img;
}
//for Flip function it swaps two values by reference.
void Swap(char*a, char*b)
{
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void Flip(int*height, int*width, int flag, char**img)
{
	int i, j;
	
	if (flag == 0)
	{
		for (i = 0;i < *height / 2;i++)
		{
			char* tmp = *(img + i);
			*(img + i) = *(img + *height - i - 1);
			*(img + *height - i - 1) = tmp;
		}
	}
	else
	{
		for (i = 0;i < *height;i++)
			for (j = 0;j < *width / 2;j++)
				Swap(*(img + i) + j, *(img + i) + *width - j-1);
	}
}
//Flower of Pointer... 
char* Copy(int x1, int y1, int c_h, int c_w, int height, int width, char**img, int x2, int y2)
{
	int i, j;
	char*tmp;
	int *ptr;
	char***ptr2;
	char**data;
	//over height and over width.Case1
	if ((width - x1 < c_w) && (height - y1 < c_h))
	{
		data = AllocateImage(height - y1, width - x1);
		//TODO : copy img value to data
		for (i = y1; i < height;i++)
		{
			for (j = x1;j < width;j++)
			{
				*(*(data + i - y1) + j - x1) = *(*(img + i) + j);
			}
		}

		tmp = (char*)malloc(sizeof(int) * 2 + sizeof(char**));
		ptr = (int*)tmp;
		*(ptr + 0) = height - y1;
		*(ptr + 1) = width-x1;
	}
	//just over width.Case2
	else if ((height - y1 > c_h) && (width - x1 < c_w))
	{
		data = AllocateImage(c_h, width - x1);
		//TODO: copy img value to data
		for (i = y1; i < y1 + c_h;i++)
		{
			for (j = x1; j < width;j++)
			{
				*(*(data + i - y1) + j - x1) = *(*(img + i) + j);
			}
		}
		tmp = (char*)malloc(sizeof(int) * 2 + sizeof(char**));
		ptr = (int*)tmp;
		*(ptr + 0) = c_h;
		*(ptr + 1) = width -x1;
	}
	//just over height Case3
	else if((height - y1 <c_h)&& (width-x1 >c_w))
	{
		data = AllocateImage(height -y1, c_w);
		//TODO copy img value to data
		for (i = y1; i < height; i++)
		{
			for (j = x1;j < x1 + c_w;j++)
			{
				*(*(data + i - y1) + j - x1) = *(*(img + i) + j);
			}
		}
		tmp = (char*)malloc(sizeof(int) * 2 + sizeof(char**));
		ptr = (int*)tmp;
		*(ptr + 0) = height -y1;
		*(ptr + 1) = c_w;
	}
	else
	{
		data = AllocateImage(c_h, c_w);

		for (i = y1; i < y1 + c_h;i++)
			for (j = x1; j < x1 + c_w; j++)
				*(*(data + i - y1) + j - x1) = *(*(img + i) + j);

		tmp = (char*)malloc(sizeof(int) * 2 + sizeof(char**));
		ptr = (int*)tmp;
		*(ptr + 0) = c_h;
		*(ptr + 1) = c_w;
	}
	
	/*
	tmp = (char*)malloc(sizeof(int) * 2 + sizeof(char**));
	ptr = (int*)tmp;
	*(ptr + 0) = c_h;
	*(ptr + 1) = c_w;
	*/
	
	ptr2 = (char***)(ptr + 2);
	*ptr2 = data;

	return tmp;
}
void Paste(int x2, int y2, int height, int width, char**img, char*tmp)
{
	int i, j;
	int c_h, c_w;
	int *ptr;
	char**data;
	ptr = (int*)tmp;
	c_h = *(ptr + 0);
	c_w = *(ptr + 1);
	data = *(char***)(ptr + 2);

	//c_h : data array's height.
	//c_w : data array's width.

	//case1
	if (((width - x2) > c_w) && ((height - y2) > c_h))
	{
		for (i = y2;i < height;i++)
		{
			for (j = x2; j < width;j++)
				*(*(img + i) + j) = *(*(data + i - y2) + j - x2);
		}
	}
	//case2
	else if (((width - x2) > c_w) && ((y2 + c_h) < height))
	{
		for (i = y2;i < y2 + c_h;i++)
		{
			for (j = x2;j < width;j++)
				*(*(img + i) + j) = *(*(data + i - y2) + j - x2);
		}
	}
	else if (( (x2+c_w) < width) && ((y2 + c_h) > height))
	{
		for (i = y2;i < height;i++)
		{
			for (j = x2; j < x2 + c_w;j++)
				*(*(img + i) + j) = *(*(data + i - y2) + j - x2);
		}
	}
	else
	{
		for (i = 0;i < c_h;i++)
		{
			for (j = 0;j < c_w;j++)
				*(*(img + y2 + i) + x2 + j) = *(*(data + i) + j);
		}
	}
		
	

	DeallocateImage(data, c_h, c_w);
}
//use Dfs,BFs
void Fill(char**img,int h,int w,int x,int y,char color)
{
	int i,nx,ny;
	int *dx = (int*)malloc(sizeof(int) * 4);
	int *dy = (int*)malloc(sizeof(int) * 4);

	*(dx + 0) = 0;
	*(dx + 1) = 0;
	*(dx + 2) = 1;
	*(dx + 3) = -1;

	*(dy + 0) = 1;
	*(dy + 1) = -1;
	*(dy + 2) = 0;
	*(dy + 3) = 0;

	
	char curColor = *(*(img + y) + x);
	*(*(img + y) + x) = color; 

	for (i = 0;i < 4;i++)
	{
		nx = x + *(dx + i);
		ny = y + *(dy + i);

		//boundary check!
		if (nx < 0 || nx >= w || ny < 0 || ny >= h)
			continue;
		//color check!
		if (*(*(img + ny) + nx) != curColor)
			continue;

		Fill(img, h, w, nx, ny, color);
	}
	
}
void Fill_ex(char**img,int h,int w,int x,int y,char color)
{
	int sx = x;
	int sy = y;
	Fill(img, h, w, sx, sy, color);
}
//count pixel.
void Fill_Count(char**img,int h,int w,char color,int *pixel)
{	
	int i, j;

	for (i = 0;i < h;i++)
	{
		for (j = 0;j < w;j++)
		{
			if (*(*(img + i) + j) == color)
				*pixel = *pixel + 1;
		}
	}
}
