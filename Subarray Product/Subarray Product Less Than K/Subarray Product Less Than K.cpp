// Subarray Product Less Than K.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void getint(string& const s, vector<int>* nums)
{
	if (s.size() == 0)
		return;
	int i = 0;
	while (i < s.size())
	{
		int buffer = 0;
		int found = 0;
		int neg = 0;
		if (s[i] == '-')
			neg = 1;
		while (i < s.size() && isdigit(s[i]))
		{
			buffer *= 10;
			buffer += s[i] - '0';
			i++;
			found = 1;
		}
		if (found)
		{
			if (neg)
				buffer = -buffer;
			(*nums).push_back(buffer);
		}
		i++;
	}
}

int numSubarrayProductLessThanK(vector<int>& nums, int k)
{
	sort(nums.begin(), nums.end());
	int count = 0;
	vector<vector<vector<int>>> subarrs;
	vector<vector<int>> products;
	subarrs.push_back(vector<vector<int>>());
	products.push_back(vector<int>());
	int i = 0;
	while (i < nums.size() && nums[i] < k)
	{
		subarrs[0].push_back(vector<int>(1, i));
		products[0].push_back(nums[i]);
		i++;
		for (auto n : subarrs[0].back())
			cout << nums[n]<<' ';
		cout << '\n';
		count++;
	}
	for (int len = 1; len < nums.size(); len++)
	{
		subarrs.push_back(vector<vector<int>>());
		products.push_back(vector<int>());
		for (int i = 0; i < subarrs[len - 1].size(); i++)
		{
			int prod = products[len - 1][i];
			int j = subarrs[len - 1][i].back() + 1;
			if (j < nums.size())
			{
				int newProd = prod * nums[j];
				while (newProd < k)
				{
					while (j < nums.size() - 1 && nums[j] == nums[j + 1])
						j++;
					vector<int> newFormula = vector<int>(subarrs[len - 1][i]);
					newFormula.push_back(j);
					subarrs[len].push_back(newFormula);
					products[len].push_back(newProd);
					for (auto n : subarrs[len].back())
						cout << nums[n] << ' ';
					cout << '\n';
					count++;
					j++;
					if (j == nums.size())
						break;
					newProd = prod * nums[j];
				}
			}
		}
	}
	return count;
}


int main()
{
	while (1)
	{
		vector<int> nums;
		cout << "Input your numbers:\n";
		string raw;
		getline(cin, raw);
		int k;
		cout << "Input target:\n";
		cin >> k;
		getint(raw, &nums);
		int numsubarray = numSubarrayProductLessThanK(nums, k);
		cout << numsubarray << endl;
		cin.ignore(100, '\n');
		cin.clear();
	}
	return 0;
}

