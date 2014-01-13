/*
ID: wentcui1
LANG: C++
TASK: cryptcow
*/
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

// Begin the Escape execution at the Break of Dawn

ofstream fileout("cryptcow.out");
string strNormal = "Begin the Escape execution at the Break of Dawn";
string strInput;
int strInputLen = 0;
int arrChNum[2][53];

bool bEable = false;
int nRs = 0;
const int HashSize = 362881;
/*
struct SHash 
{
    char* str;
    SHash* pNext;
    SHash():str(NULL), pNext(NULL){}
};
*/

//SHash* hashTable[HashSize];
bool hashTable[HashSize];

unsigned int BKDR_Hash(const string& ss)
{
    unsigned int nSeed = 131;
    unsigned int nHash = 0;
    int nLen = ss.length();
    for (int i = 0; i < nLen; i++)
        nHash = nHash * nSeed + (unsigned int)ss[i];
    return nHash % HashSize;
}

bool prepairData()
{
    memset(arrChNum, 0, sizeof(arrChNum));
    memset(hashTable, 0, sizeof(hashTable));
    ifstream filein("cryptcow.in");
    getline(filein, strInput);
	if (strInput.size() == strNormal.size()) {
    	fileout << 1 << " " << 0 << endl;
	} else
		return false;
		
    filein.close();
    strInputLen = strInput.size();
    int nNumC = 0, nNumO = 0, nNumW = 0, nNumSp = 0;
    int arrPosC[9], arrPosO[9], arrPosW[9], arrPosSp[30];
    for (int i = 0; i < strInputLen; i++)
    {
        if (strInput[i] == 'C')
        {
            arrPosC[nNumC++] = i;
        }
        else if (strInput[i] == 'O')
        {
            arrPosC[nNumO++] = i;
        }
        else if (strInput[i] == 'W')
        {
            arrPosW[nNumW++] = i;
        }
        else
        {
            if (strInput[i] >= 'A' && strInput[i] <= 'Z')
                arrChNum[1][strInput[i] - 'A']++;
            else if (strInput[i] >= 'a' && strInput[i] <= 'z')
                arrChNum[1][strInput[i] - 'a' + 26]++;
            else
                arrChNum[1][52]++;
        }
        if (nNumC > 9 || nNumO > 9 || nNumW > 9)
        {
            return false;
        }
    }
    // C O W ????
    if (nNumC != nNumO || nNumO != nNumW)
        return false;

    for (int i = 0; i < 47; i++)
    {
        if (strNormal[i] >= 'A' && strNormal[i] <= 'Z')
            arrChNum[0][strNormal[i] - 'A']++;
        else if(strNormal[i] >= 'a' && strNormal[i] <= 'z')
            arrChNum[0][strNormal[i] - 'a' + 26]++;
        else
            arrChNum[0][52]++;
    }
    // ???????
    for (int i = 0; i < 53; i++)
    {
        if (arrChNum[0][i] != arrChNum[1][i])
            return false;
    }

    nRs = nNumC;
    return true;
}

bool dfs(string ss)
{
    int nNumC = 0, nNumO = 0, nNumW = 0, nNumSp = 0;
    int arrPosC[9], arrPosO[9], arrPosW[9], arrPosSp[30];
    int nStrLen = ss.length();
    if (nStrLen == 47)
        return ss.compare(strNormal) == 0;

    for (int i = 0; i < nStrLen; i++)
    {
        if (ss[i] == 'C')
        {
            arrPosC[nNumC++] = i;
            arrPosSp[nNumSp++] = i;
        }
        else if (ss[i] == 'O')
        {
            arrPosO[nNumO++] = i;
            arrPosSp[nNumSp++] = i;
        }
        else if (ss[i] == 'W')
        {
            arrPosW[nNumW++] = i;
            arrPosSp[nNumSp++] = i;
        }
    }

    if (arrPosSp[0] != arrPosC[0] || arrPosSp[nNumSp - 1] != arrPosW[nNumW - 1])
        return false;

    string strSub = "";
    if (arrPosSp[0] != 0)
    {
        strSub = ss.substr(0, arrPosSp[0]);
        // ?????????
        if (strSub.compare(strNormal.substr(0, arrPosSp[0])) != 0)
            return false;
    }
    if (arrPosSp[nNumSp - 1] != nStrLen - 1)
    {
        strSub = ss.substr(arrPosSp[nNumSp - 1] + 1, nStrLen - arrPosSp[nNumSp - 1] - 1);
        // ?????????
        if (strSub.compare(strNormal.substr(47 - nStrLen + arrPosSp[nNumSp - 1] + 1, nStrLen - arrPosSp[nNumSp - 1] - 1)) != 0)
            return false;
    }

    for (int i = 0; i <= nNumSp - 2; i++)
    {
        strSub = ss.substr(arrPosSp[i] + 1, arrPosSp[i + 1] - arrPosSp[i] - 1);
        if (strSub.length() == 0)
            continue;
        else if (strSub.length() == 47)
            return strSub.compare(strNormal) == 0;
        else
        {
            unsigned int nHash = BKDR_Hash(strSub);
            if (strNormal.find(strSub) == string::npos)
                return false;
        }
    }

    for (int i = 0; i < nNumC; i++)
        for (int j = 0; j < nNumO; j++)
        {
            if (arrPosO[j] < arrPosC[i])
                continue;
            for (int k = nNumW - 1; k >= 0; k--)
            {
                if (arrPosW[k] < arrPosO[j])
                    continue;
                string s0 = ss.substr(0, arrPosC[i]);
                string s1 = ss.substr(arrPosC[i] + 1, arrPosO[j] - arrPosC[i] - 1);
                string s2 = ss.substr(arrPosO[j] + 1, arrPosW[k] - arrPosO[j] - 1);
                string s3 = ss.substr(arrPosW[k] + 1, nStrLen - arrPosW[k] - 1);
                string newSS = s0 + s2 + s1 + s3;
                bool bSkip = false;
                for (int i = 0; i < newSS.length(); i++)
                {
                    if (newSS[i] == 'C')
                        break;
                    else if (newSS[i] == 'O' || newSS[i] == 'W')
                    {
                        bSkip = true;
                        break;
                    }
                }
                if (bSkip)
                    continue;
                for (int i = newSS.length() - 1; i >= 0; i--)
                {
                    if (newSS[i] == 'W')
                        break;
                    else if (newSS[i] == 'O' || newSS[i] == 'C')
                    {
                        bSkip = true;
                        break;
                    }
                }
                if (bSkip)
                    continue;

                    unsigned int nHash = BKDR_Hash(newSS);
                    /*
                    SHash* pHash = hashTable[nHash];
                    SHash* pPreHash = NULL;
                    while (pHash && pHash->str)
                    {
                        if (strcmp(pHash->str, newSS.c_str()) == 0)
                        {
                            bSkip = true;
                            break;
                        }
                        pPreHash = pHash;
                        pHash = pHash->pNext;
                    }
                    if (bSkip)
                        continue;
                    */
                    if (!hashTable[nHash])
                    {
                        if (dfs(newSS))
                            return true;
                        else
                            hashTable[nHash] = true;
                    }
                    /*    
                    if (dfs(newSS))
                    return true;
                    
                    pHash = new SHash();
                    pHash->str = new char[newSS.length() + 1];
                    strcpy(pHash->str, newSS.c_str());
                    if (pPreHash)
                        pPreHash->pNext = pHash;
                    */
            }
        }
        return false;
}

void process()
{
    bEable = dfs(strInput);
    if (!bEable)
        nRs = 0;
}

int main(){
    if(prepairData())
    {
        process();
    }
    fileout.close();    
    return 0;
}
