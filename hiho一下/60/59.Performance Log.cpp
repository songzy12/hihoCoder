#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRING_SIZE 256

struct node
{
	int hour;
	int minute;
	int second;
	char* name;
	int order;
};

int main()
{
	int num;
	char temp[6];
	struct node* stack_head;
	struct node* result_head;
	struct node* tmp;
	char*name;
	int index = 0;
	int order = 0;
	int last_time;
	int i;

	scanf("%d", &num);
	stack_head = (struct node*)malloc(num*sizeof(struct node));
	result_head = (struct node*)malloc(num / 2 * sizeof(struct node));
	for (i = 0; i < num; i++)
	{
		tmp = stack_head + i;
		tmp->name = NULL;
	}
	for (i = 0; i < num; i++)
	{
		tmp = stack_head + index;
		tmp->name = (char*)malloc(STRING_SIZE);
		scanf("%s %d:%d:%d %s", tmp->name, &(tmp->hour),
			&(tmp->minute), &(tmp->second), temp); // read
		if(0==i)
		{
		    last_time = tmp->hour * 3600 + tmp->minute * 60 + tmp->second;
		}
		else
		{
		    if(last_time-tmp->hour * 3600 - tmp->minute * 60 - tmp->second>=0)
		    {
		        index=1;
		        break;
		    }
		    else
		        last_time=tmp->hour * 3600 + tmp->minute * 60 + tmp->second>=0;
		}
		if (strcmp(temp, "END") == 0)
		{
			if (0 == index)
			{
				index = 1;
				break;
			}
			else if (strcmp(tmp->name, (tmp-1)->name)==0)
			{
				int hour, minute, second, time;
				
				(result_head + (tmp - 1)->order)->name = tmp->name;
				
                time = tmp->hour * 3600 + tmp->minute * 60 + tmp->second;
				
                time -= (tmp - 1)->hour * 3600 + (tmp - 1)->minute * 60 + (tmp - 1)->second;
				(result_head + (tmp - 1)->order)->hour = time / 3600;
				
                time %= 3600;
				(result_head + (tmp - 1)->order)->minute = time / 60;
				
                time %= 60;
				(result_head + (tmp - 1)->order)->second = time;
                
				index--;
				
			}
			else
			{
				index = 1;
				break;
			}
		}
		else
		{
			tmp->order = order++;
			index++;
		}
		
	}
	if (0 == index)
	{
		for (i = 0; i < num / 2; i++)
		{
			tmp = result_head + i;
			printf("%s %02d:%02d:%02d\n", tmp->name, tmp->hour, tmp->minute, tmp->second); // write
		}
	}
	else
	{
		printf("Incorrect performance log\n");
	}
	free(result_head);
	for (i = 0; i < num; i++)
	{
		tmp = stack_head + i;
		free(tmp->name);
	}
	free(stack_head);
	return 0;
}

