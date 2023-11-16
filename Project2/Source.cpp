//Project2.cpp
//This project is the kaprekar function brought to all bases, displaying the k-number and loop length number as k.l for the table.

#include <iostream>
#include <cmath>
//#define DEBUG

using namespace std;

struct container
{
	bool not_same = true;
	double value = 0;
	int counter = 0;
	int number_of_times_played = 0;
	int game_number = 0;
	double base_value = 0;
	int whole_base = 0;
	int whole_number = 0;
	int loop_length = 0;
}c;

void get_input_pt_1(container* c);
void game_2(container* c);
void game_1(container* c);
void sort_array(int digits[]);
double kaprekate(container* c, int array[]);

int main()
{
	char response = 'o';
	while (response != 'n')
	{
		cout << "Want to play ";
		if (c.number_of_times_played == 0)
		{
			cout << "a game?\n\ny/n: ";
			cin >> response;
		}
		else
		{
			cout << "again?\n\ny/n: ";
			cin >> response;
		}
		
		if (response != 'n')
		{
			if (response == 'y')
			{
				get_input_pt_1(&c);
				if (c.game_number == 1)
				{
					cout << "\n\nYou chose single number style!\n";

					game_1(&c);
					
					cout << endl << endl;
				}
				else if (c.game_number == 2)
				{
					cout << "\n\nYou chose base chart style!\n";

					game_2(&c);

					cout << endl << endl;
					c.number_of_times_played++;
				}
				else if (c.game_number == 0)
				{
					response = 'n';
				}
			}
			else
			{
				cout << "\n\nNot a choice, just pick y or n...\n" << endl;
			}
		}
		if (response == 'n')
		{
			cout << "\nPlayed " << c.number_of_times_played;
			if (c.number_of_times_played == 0 || c.number_of_times_played > 1)
			{
				cout << " times.";
			}
			else if (c.number_of_times_played == 1)
			{
				cout << " time.";
			}
			cout << "\n\n\n~Bye!~\n" << endl;
		}
	}
	return 0;
}

void get_input_pt_1(container* c)
{
	bool flag_repeat = true;
	while (flag_repeat == true)
	{
		cout << "\nChoose to play either single number (1) or base chart (2) style, or 0 to quit: ";
		cin >> c->game_number;
		if (c->game_number == 1 || c->game_number == 2 || c->game_number == 0)
		{
			flag_repeat = false;
		}
		else
		{
			cout << "\n\nI'm afraid that just isn't an option.. try again.\n";
		}
	}
}

void game_2(container* c)
{
	int array[32] = {};
	cout << "\nChoose the positive whole-number base value (less than 20) that you want to view the chart for\n";
	cout << "Note: Larger bases have longer charts, so after a certain base number the beginning will be lost after the program ends.\n\nbase: ";
	cin >> c->base_value;
	c->whole_base = floor(c->base_value);
	cout << "\n\n";
	for (int i = 0; i < c->whole_base; i++)
	{
		for (int j = 0; j < c->whole_base; j++)
		{
			for (int k = 0; k < c->whole_base; k++)
			{
				for (int l = 0; l < c->whole_base; l++)
				{
					c->whole_number = i * pow(c->whole_base, 3) + j * pow(c->whole_base, 2) + k * c->whole_base + l;
					cout << kaprekate(c, array) << "." << c->loop_length << " ";
					c->counter = 0;
					c->not_same = true;
				}
				cout << "\n\n";
			}
			cout << "\n";
		}
		cout << "\n\n";
	}
}

void game_1(container* c)
{
	cout << "\nBegin by choosing a positive whole-number base value: ";
	cin >> c->base_value;
	c->whole_base = floor(c->base_value);
	cout << "\n\nNow enter the number you wish to analyze: ";
	cin >> c->value;
	
	c->whole_number = floor(c->value);
	
	if (c->whole_number >= pow(c->base_value, 4))
	{
		cout << "\nNumber is a bit too large for the chosen base, so that doesn't count.\n\n";
	}
	else if (c->whole_number == 0)
	{
		cout << "\n0 is just 0... that doesn't count.\n";
	}
	else
	{
		int array[32] = {};
		cout << "\n\nk = " << kaprekate(c, array) << "\n\n";
		c->number_of_times_played++;
		c->counter = 0;
		c->not_same = true;
	}
}

void sort_array(int digits[])
{
	int temp_var = 0;
	int smallest_value = 0;
	for (int i = 0; i < 4; i++)
	{
		int smallest_index = i;
		for (int j = i + 1; j < 4; j++)
		{
			if (digits[j] < digits[smallest_index])
			{
				smallest_index = j;
			}
		}
		if (smallest_index != i)
		{
			temp_var = digits[i];
			digits[i] = digits[smallest_index];
			digits[smallest_index] = temp_var;
		}
	}
}

double kaprekate(container* c, int array[])
{
	int digits[4] = {0, 0, 0, 0};
	for (int i = 3; i > -1; i--)
	{
		digits[i] = c->whole_number % c->whole_base;
		c->whole_number -= digits[i];
		c->whole_number /= c->whole_base;
	}
	if (digits[0] == digits[1] && digits[1] == digits[2] && digits[2] == digits[3])
	{
		c->loop_length = 0;
		return 0;
	}
	else
	{
		sort_array(digits);
#ifdef DEBUG
	if (c->game_number == 1)
	{
		cout << "\nsorted array: ";

		for (int j = 0; j < 4; j++)
		{
			cout << digits[j] << " ";
		}
		cout << "\nEnd Debug.\n\n";
	}

#endif
		array[c->counter] = digits[0] * pow(c->whole_base, 3) + digits[1] * pow(c->whole_base, 2) + digits[2] * c->whole_base + digits[3];
		int largest_value = digits[3] * pow(c->whole_base, 3) + digits[2] * pow(c->whole_base, 2) + digits[1] * c->whole_base + digits[0];
		int difference = largest_value - array[c->counter];
		for (int k = 3; k > -1; k--)
		{
			digits[k] = difference % c->whole_base;
			difference -= digits[k];
			difference /= c->whole_base;
		}
		sort_array(digits);
#ifdef DEBUG
		if (c->game_number == 1)
		{
		cout << "array[" << c->counter << "] = " << array[c->counter] << "\n";
		cout << "\n2nd sorted array: ";

		for (int j = 0; j < 4; j++)
		{
			cout << digits[j] << " ";
		}
		cout << "\nEnd 2nd Debug.\n\n";
	}
#endif
		int smallest_value = digits[0] * pow(c->whole_base, 3) + digits[1] * pow(c->whole_base, 2) + digits[2] * c->whole_base + digits[3];
		for (int l = 0; l < c->counter + 1; l++)
		{
			if (array[l] == smallest_value)
			{
				c->loop_length = c->counter - l;
				if (c->game_number == 1)
				{
					cout << "\n\nl = " << c->loop_length << "\n\n";
				}
				c->not_same = false;
			}
		}
		if (c->not_same == false)
		{
			if (c->counter == 0)
			{
				c->loop_length++;
			}
			return c->counter;
		}
		else if (c->not_same == true)
		{
			c->whole_number = smallest_value;
			c->counter++;
			return kaprekate(c, array);
		}
	}
}