#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <vector> 
#include <cstdlib>
#include <windows.h>
#include <map> 
#include <vector> 
using namespace std;

//utf-8תΪansi���� 
string UnicodeToANSI(const std::wstring& strUnicode)
{
	int nAnsiLen = WideCharToMultiByte(CP_ACP,
		0,
		strUnicode.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
 
	char *pAnsi = new char[nAnsiLen + 1];
	memset((void*)pAnsi, 0, (nAnsiLen + 1) * sizeof(char));
 
	::WideCharToMultiByte(CP_ACP,
		0,
		strUnicode.c_str(),
		-1,
		pAnsi,
		nAnsiLen,
		NULL,
		NULL);
 
	std::string strAnsi;
	strAnsi = pAnsi;
	delete[]pAnsi;
 
	return strAnsi;
}
wstring UTF8ToUnicode(const std::string& str)
{
	int nUnicodeLen = ::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
 
	wchar_t*  pUnicode;
	pUnicode = new wchar_t[nUnicodeLen + 1];
	memset((void*)pUnicode, 0, (nUnicodeLen + 1) * sizeof(wchar_t));
 
	::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		nUnicodeLen);
 
	std::wstring  strUnicode;
	strUnicode = (wchar_t*)pUnicode;
	delete []pUnicode;
 
	return strUnicode;
}
string Utf8ToAnsi(const std::string &strUtf8)
{
	std::wstring strUnicode = UTF8ToUnicode(strUtf8);
	return UnicodeToANSI(strUnicode);
}


//��ȡ�ض���ʽ���ļ���    
void getAllFiles(string path, vector<string>& files,string format)
{	
	intptr_t  hFile = 0;//�ļ����  64λ��long ��Ϊ intptr_t
	struct _finddata_t fileinfo;//�ļ���Ϣ 
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1) //�ļ�����
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))//�ж��Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)//�ļ������в���"."��".."
				{
					files.push_back(p.assign(path).append(fileinfo.name)); //�����ļ�����
					getAllFiles(p.assign(path).append(fileinfo.name), files,format); //�ݹ�����ļ���
				}
			}
			else
			{
				files.push_back(p.assign(path).append(fileinfo.name));//��������ļ��У������ļ���
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


int main(int argc, char** argv) {

	//���������ʽ��¼�ṹ 
	int outTypeSet = 0;
	vector<string> outType;
	int outProvincesSet = 0;
	string provincesList[] = {"ȫ��","����","����","����","����","����","�㶫","����","����","����","�ӱ�","����","������","����","����","����","����","����","����","���ɹ�","����","�ຣ","ɽ��","ɽ��","����","�Ϻ�","�Ĵ�","���","����","�½�","����","�㽭"}; 
	map<string,int> provincesOut;
	provincesOut["ȫ��"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["�㶫"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["�ӱ�"] = 0;
	provincesOut["����"] = 0;
	provincesOut["������"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["����"] = 0;
	provincesOut["���ɹ�"] = 0;
	provincesOut["����"] = 0;
	provincesOut["�ຣ"] = 0;
	provincesOut["ɽ��"] = 0;
	provincesOut["ɽ��"] = 0;
	provincesOut["����"] = 0; 
	provincesOut["�Ϻ�"] = 0;
	provincesOut["�Ĵ�"] = 0;
	provincesOut["���"] = 0;
	provincesOut["����"] = 0;
	provincesOut["�½�"] = 0;
	provincesOut["����"] = 0;
	provincesOut["�㽭"] = 0;

	//���ø�ʡ����ͳ��map�ṹ 
	map<string,int> provincesUndef;
	map<string,int> provincesDef;
	map<string,int> provincesCure;
	map<string,int> provincesDie;
	provincesUndef["ȫ��"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["�㶫"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["�ӱ�"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["������"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["���ɹ�"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["�ຣ"] = 0;
	provincesUndef["ɽ��"] = 0;
	provincesUndef["ɽ��"] = 0;
	provincesUndef["����"] = 0; 
	provincesUndef["�Ϻ�"] = 0;
	provincesUndef["�Ĵ�"] = 0;
	provincesUndef["���"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["�½�"] = 0;
	provincesUndef["����"] = 0;
	provincesUndef["�㽭"] = 0;
	provincesDef["ȫ��"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["�㶫"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["�ӱ�"] = 0;
	provincesDef["����"] = 0;
	provincesDef["������"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["����"] = 0;
	provincesDef["���ɹ�"] = 0;
	provincesDef["����"] = 0;
	provincesDef["�ຣ"] = 0;
	provincesDef["ɽ��"] = 0;
	provincesDef["ɽ��"] = 0;
	provincesDef["����"] = 0; 
	provincesDef["�Ϻ�"] = 0;
	provincesDef["�Ĵ�"] = 0;
	provincesDef["���"] = 0;
	provincesDef["����"] = 0;
	provincesDef["�½�"] = 0;
	provincesDef["����"] = 0;
	provincesDef["�㽭"] = 0;
	provincesCure["ȫ��"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["�㶫"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["�ӱ�"] = 0;
	provincesCure["����"] = 0;
	provincesCure["������"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["����"] = 0;
	provincesCure["���ɹ�"] = 0;
	provincesCure["����"] = 0;
	provincesCure["�ຣ"] = 0;
	provincesCure["ɽ��"] = 0;
	provincesCure["ɽ��"] = 0;
	provincesCure["����"] = 0; 
	provincesCure["�Ϻ�"] = 0;
	provincesCure["�Ĵ�"] = 0;
	provincesCure["���"] = 0;
	provincesCure["����"] = 0;
	provincesCure["�½�"] = 0;
	provincesCure["����"] = 0;
	provincesCure["�㽭"] = 0;
	provincesDie["ȫ��"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["�㶫"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["�ӱ�"] = 0;
	provincesDie["����"] = 0;
	provincesDie["������"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["����"] = 0;
	provincesDie["���ɹ�"] = 0;
	provincesDie["����"] = 0;
	provincesDie["�ຣ"] = 0;
	provincesDie["ɽ��"] = 0;
	provincesDie["ɽ��"] = 0;
	provincesDie["����"] = 0; 
	provincesDie["�Ϻ�"] = 0;
	provincesDie["�Ĵ�"] = 0;
	provincesDie["���"] = 0;
	provincesDie["����"] = 0;
	provincesDie["�½�"] = 0;
	provincesDie["����"] = 0;
	provincesDie["�㽭"] = 0;
	string targetProvince; 
	string filePath("C:\\Users\\Administrator\\Documents\\GitHub\\221701335\\example\\log\\");
	string outPath;
	string file;
	string date("2020-01-29");

	
	
	char temp[256];
	int numTemp;
	string option;
	for(int i = 1; i<argc; i++){
		option = argv[i];
		if(option == "-log"){
			filePath = argv[++i];
		}
		else if(option == "-out"){
			outPath = argv[++i];
		}
		else if(option == "-date"){
			date = argv[++i];
		}
		else if(option == "-type"){
			outTypeSet = 1;
			while(argv[i+1] == "ip"||argv[i+1] == "sp"||argv[i+1] == "cure"||argv[i+1] == "dead") {
				option = argv[++i];
				outType.push_back(option);				
			}
		}
		else if(option == "-province"){
			outProvincesSet = 1;
			map<string,int>::iterator it;
			it = provincesOut.find(argv[i+1]);
			while(it != provincesOut.end()){
				option = argv[++i];
				provincesOut.at(option) = 1;
				it = provincesOut.find(argv[i+1]);
			}
		}
		else{
			cout<<"�����������"<<endl;
			return -1;
		}
	}
	
	
	if(filePath.length() == 0){
		cout<<"-log����δָ��"<<endl;
		return -1;	
	} 
	
	if(date.length() != 0){
		string dateTemp = date;
		date = filePath;
		date.append(dateTemp);
		date.append(".log.txt");
	}
	
	//��ȡ��־�ļ��� 
	vector<string> files;
	string format = "";	//.txt
	getAllFiles(filePath, files, format);
	int size = files.size();
	
	/* 
	//�����ã�������� 
	cout<<endl;
	cout<<"date:"<<endl;
	cout<<date<<endl;
	cout<<"___________________________________________"<<endl;
	*/
	
	cout<<endl;
	cout<<"date:"<<endl;
	cout<<date<<endl;
	cout<<"___________________________________________"<<endl;
	cout<<endl;
	cout<<"path:"<<endl;
	cout<<filePath<<endl;
	cout<<"___________________________________________"<<endl;
	
	for (int i = 0; i<size; i++){	
		if(date.length() != 0){
			cout << files[i] << " :" <<endl;
			if(files[i] > date)
			
				continue;		
		}
		//cout << files[i] << " :" <<endl;
		char *filepath = const_cast<char *>(files[i].c_str()) ;
		//cout << filepath << " :" <<endl;
		ifstream fin(filepath);
		//�����ĵ�����
		while(!fin.eof()){		 
			fin >> temp;
			string info = Utf8ToAnsi(temp);
			
			if(info == "//"){
				fin.getline(temp,255);
				continue;
			}
			
			targetProvince = info;
			fin >> temp;
			info = Utf8ToAnsi(temp);
			
			if(info == "�ų�"){
				fin >> temp;
				fin >> numTemp;
				fin >> temp;
				provincesUndef.at(targetProvince) -= numTemp;
				provincesUndef.at("ȫ��") -= numTemp;
			}
			
			else if(info == "����"){
				fin >> numTemp;
				fin >> temp;
				provincesDie.at(targetProvince) += numTemp;
				provincesDie.at("ȫ��") += numTemp;
				provincesDef.at(targetProvince) -= numTemp;
				provincesDef.at("ȫ��") -= numTemp;
			}
			
			else if(info == "����"){
				fin >> numTemp;
				fin >> temp;
				provincesCure.at(targetProvince) += numTemp;
				provincesCure.at("ȫ��") += numTemp;
				provincesDef.at(targetProvince) -= numTemp;
				provincesDef.at("ȫ��") -= numTemp;
			}
			
			else if(info == "����"){
				fin >> temp;
				info = Utf8ToAnsi(temp);
				if(info == "��Ⱦ����") {
					fin >> numTemp;
					fin >> temp;
					provincesDef.at(targetProvince) += numTemp;
					provincesDef.at("ȫ��") += numTemp;
				} 
				else if(info == "���ƻ���"){
					fin >> numTemp;
					fin >> temp;
					provincesUndef.at(targetProvince) += numTemp;
					provincesUndef.at("ȫ��") += numTemp;
				} 
				else{
					cout << targetProvince << "����ĵ����ݴ���" << endl;
					fin.getline(temp,255);
					continue;
				} 
			}
			
			else if(info == "��Ⱦ����"){
				fin >> temp;
				fin >> temp; 
				string tempProvince = Utf8ToAnsi(temp);
				fin >> numTemp;
				fin >> temp;
				provincesDef.at(targetProvince) -= numTemp;
				provincesDef.at(tempProvince) += numTemp;
			}
			
			else if(info == "���ƻ���"){
				fin >> temp;
				info = Utf8ToAnsi(temp);
				if(info == "ȷ���Ⱦ"){
					fin >> numTemp;
					fin >> temp;
					provincesDef.at(targetProvince) += numTemp;
					provincesDef.at("ȫ��") += numTemp;
					provincesUndef.at(targetProvince) -= numTemp;
					provincesUndef.at("ȫ��") -= numTemp;
				}
				else if(info == "����"){
					fin >> temp; 
					string tempProvince = Utf8ToAnsi(temp);
					fin >> numTemp;
					fin >> temp;
					provincesUndef.at(targetProvince) -= numTemp;
					provincesUndef.at(tempProvince) += numTemp;
				}
				else{
					cout << targetProvince<<"����ĵ����ݴ���"<<endl;
					fin.getline(temp,255);
					continue; 
				} 	
			}
			
			else{
				cout << targetProvince<<"����ĵ����ݴ���"<<endl;
				fin.getline(temp,255);
				continue; 
			} 
		}
		//�����ĵ�������� 
	}
	//����ָ���ĵ��������
	
	for(int i = 1; i<argc; i++){
		;
	}
	if(file.length() == 0){
		cout << "aaaaaaa";
	}
	int len = file.length();
	cout << len;
	
	cout << "Undef:" <<endl;
	for (map<string, int>::iterator iter = provincesUndef.begin(); iter != provincesUndef.end(); iter++)
    	cout << iter->first << " ==> " << iter->second << endl;
    cout << "Def:" <<endl;
    for (map<string, int>::iterator iter = provincesDef.begin(); iter != provincesDef.end(); iter++)
		cout << iter->first << " ==> " << iter->second << endl;
	cout << "Cure:" <<endl;
    for (map<string, int>::iterator iter = provincesCure.begin(); iter != provincesCure.end(); iter++)
		cout << iter->first << " ==> " << iter->second << endl;
	cout << "Die:" <<endl;
    for (map<string, int>::iterator iter = provincesDie.begin(); iter != provincesDie.end(); iter++)
		cout << iter->first << " ==> " << iter->second << endl;
	return 0;
}
