// Top K Frequent Words.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <map>
#include <unordered_map>
using namespace std;

vector<string> readWords()
{
	vector<string> words;
	string raw;
	getline(cin, raw);
	for (int i = 0; i < raw.size(); i++)
	{
		string buffer;
		while (i < raw.size() && isalpha(raw[i]))
		{
			buffer.push_back(raw[i]);
			i++;
		}
		if (buffer.size())
			words.push_back(buffer);
	}
	return words;
}



vector<string> topKFrequent(vector<string>& words, int k)
{
	map<string, int> uniqueWords;
	for (int i = 0; i < words.size(); i++)
	{
		if (uniqueWords.find(words[i]) == uniqueWords.end())
			uniqueWords[words[i]] = 1;
		else
			uniqueWords[words[i]]++;
	}
	map<int, vector<string>> freqOfWords;
	auto It = uniqueWords.begin();
	while (It != uniqueWords.end())
	{
		freqOfWords[It->second].push_back(It->first);
		It++;
	}
	vector<string> result;
	if (k > words.size())
		return result;
	auto freqIt = freqOfWords.end();
	freqIt--;
	int i = 0;
	while (i < k)
	{
		for (int j = 0; j < freqIt->second.size() && i < k; j++)
		{
			result.push_back(freqIt->second[j]);
			i++;
		}
		freqIt--;
	}
	return result;
}


int main()
{
	ios::sync_with_stdio(false);
	cout << "Input the words:\n";
	vector<string> words = readWords();
	cout << "Input k:\n";
	int k;
	cin >> k;
	vector<string> topWords = topKFrequent(words, k);
	for (auto& wd : topWords)
		cout << wd << ", ";
	cin.ignore(100, '\n');
	cin.clear();
	getchar();
	return 0;
}

