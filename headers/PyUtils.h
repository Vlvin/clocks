#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace PyUtils {

    static string strrange(string line, int start, int end) {
        if (end < start) return NULL;
        return line.substr(start, end-start);
    }

    static vector<string> split (string tosplit, char separator) {
        int seeker = 0;
        int start = seeker;
        vector<string> ret;
        vector<string> retch;
        while (seeker < tosplit.length()) {
            for (;(tosplit[seeker] != separator) && (seeker <= tosplit.length()); seeker++);
            ret.push_back(strrange(tosplit, start, seeker));
            seeker++;
            start = seeker;
        }
        for (string seek: ret) {
            if (seek != string("") && seek != string("")+separator) retch.push_back(seek);
        }
        return retch;
    }

    static string trim(string tot) {
        int start = 0, end = tot.length() - 1;
        for (; start < tot.length(); start++) {
            if (tot[start] != ' ') break;
        }

        for (; end > -1; end--) {
            if (tot[end] != ' ') break;
        }
        return strrange(tot, start, end+1);
    }

    static bool endswith(string text, string ending) {
        return (strrange(text, (text.length() - ending.length()), text.length())) == ending;   
    }
}