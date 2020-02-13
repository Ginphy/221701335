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

//utf-8转为ansi函数 
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


//获取特定格式的文件名    
void getAllFiles(string path, vector<string>& files,string format)
{	
	intptr_t  hFile = 0;//文件句柄  64位下long 改为 intptr_t
	struct _finddata_t fileinfo;//文件信息 
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1) //文件存在
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))//判断是否为文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)//文件夹名中不含"."和".."
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name)); //保存文件夹名
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files,format); //递归遍历文件夹
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));//如果不是文件夹，储存文件名
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


int main(int argc, char** argv) {

	//设置输出格式记录结构 
	int outTypeSet = 0;
	vector<string> outType;
	
	//设置各省人数统计map结构 
	map<string,int> provincesUndef;
	map<string,int> provincesDef;
	map<string,int> provincesCure;
	map<string,int> provincesDie;
	provincesUndef["全国"] = 0;
	provincesUndef["安徽"] = 0;
	provincesUndef["北京"] = 0;
	provincesUndef["重庆"] = 0;
	provincesUndef["福建"] = 0;
	provincesUndef["甘肃"] = 0;
	provincesUndef["广东"] = 0;
	provincesUndef["广西"] = 0;
	provincesUndef["贵州"] = 0;
	provincesUndef["海南"] = 0;
	provincesUndef["河北"] = 0;
	provincesUndef["河南"] = 0;
	provincesUndef["黑龙江"] = 0;
	provincesUndef["湖北"] = 0;
	provincesUndef["湖南"] = 0;
	provincesUndef["吉林"] = 0;
	provincesUndef["江苏"] = 0;
	provincesUndef["江西"] = 0;
	provincesUndef["辽宁"] = 0;
	provincesUndef["内蒙古"] = 0;
	provincesUndef["宁夏"] = 0;
	provincesUndef["青海"] = 0;
	provincesUndef["山东"] = 0;
	provincesUndef["山西"] = 0;
	provincesUndef["陕西"] = 0; 
	provincesUndef["上海"] = 0;
	provincesUndef["四川"] = 0;
	provincesUndef["天津"] = 0;
	provincesUndef["西藏"] = 0;
	provincesUndef["新疆"] = 0;
	provincesUndef["云南"] = 0;
	provincesUndef["浙江"] = 0;
	provincesDef["全国"] = 0;
	provincesDef["安徽"] = 0;
	provincesDef["北京"] = 0;
	provincesDef["重庆"] = 0;
	provincesDef["福建"] = 0;
	provincesDef["甘肃"] = 0;
	provincesDef["广东"] = 0;
	provincesDef["广西"] = 0;
	provincesDef["贵州"] = 0;
	provincesDef["海南"] = 0;
	provincesDef["河北"] = 0;
	provincesDef["河南"] = 0;
	provincesDef["黑龙江"] = 0;
	provincesDef["湖北"] = 0;
	provincesDef["湖南"] = 0;
	provincesDef["吉林"] = 0;
	provincesDef["江苏"] = 0;
	provincesDef["江西"] = 0;
	provincesDef["辽宁"] = 0;
	provincesDef["内蒙古"] = 0;
	provincesDef["宁夏"] = 0;
	provincesDef["青海"] = 0;
	provincesDef["山东"] = 0;
	provincesDef["山西"] = 0;
	provincesDef["陕西"] = 0; 
	provincesDef["上海"] = 0;
	provincesDef["四川"] = 0;
	provincesDef["天津"] = 0;
	provincesDef["西藏"] = 0;
	provincesDef["新疆"] = 0;
	provincesDef["云南"] = 0;
	provincesDef["浙江"] = 0;
	provincesCure["全国"] = 0;
	provincesCure["安徽"] = 0;
	provincesCure["北京"] = 0;
	provincesCure["重庆"] = 0;
	provincesCure["福建"] = 0;
	provincesCure["甘肃"] = 0;
	provincesCure["广东"] = 0;
	provincesCure["广西"] = 0;
	provincesCure["贵州"] = 0;
	provincesCure["海南"] = 0;
	provincesCure["河北"] = 0;
	provincesCure["河南"] = 0;
	provincesCure["黑龙江"] = 0;
	provincesCure["湖北"] = 0;
	provincesCure["湖南"] = 0;
	provincesCure["吉林"] = 0;
	provincesCure["江苏"] = 0;
	provincesCure["江西"] = 0;
	provincesCure["辽宁"] = 0;
	provincesCure["内蒙古"] = 0;
	provincesCure["宁夏"] = 0;
	provincesCure["青海"] = 0;
	provincesCure["山东"] = 0;
	provincesCure["山西"] = 0;
	provincesCure["陕西"] = 0; 
	provincesCure["上海"] = 0;
	provincesCure["四川"] = 0;
	provincesCure["天津"] = 0;
	provincesCure["西藏"] = 0;
	provincesCure["新疆"] = 0;
	provincesCure["云南"] = 0;
	provincesCure["浙江"] = 0;
	provincesDie["全国"] = 0;
	provincesDie["安徽"] = 0;
	provincesDie["北京"] = 0;
	provincesDie["重庆"] = 0;
	provincesDie["福建"] = 0;
	provincesDie["甘肃"] = 0;
	provincesDie["广东"] = 0;
	provincesDie["广西"] = 0;
	provincesDie["贵州"] = 0;
	provincesDie["海南"] = 0;
	provincesDie["河北"] = 0;
	provincesDie["河南"] = 0;
	provincesDie["黑龙江"] = 0;
	provincesDie["湖北"] = 0;
	provincesDie["湖南"] = 0;
	provincesDie["吉林"] = 0;
	provincesDie["江苏"] = 0;
	provincesDie["江西"] = 0;
	provincesDie["辽宁"] = 0;
	provincesDie["内蒙古"] = 0;
	provincesDie["宁夏"] = 0;
	provincesDie["青海"] = 0;
	provincesDie["山东"] = 0;
	provincesDie["山西"] = 0;
	provincesDie["陕西"] = 0; 
	provincesDie["上海"] = 0;
	provincesDie["四川"] = 0;
	provincesDie["天津"] = 0;
	provincesDie["西藏"] = 0;
	provincesDie["新疆"] = 0;
	provincesDie["云南"] = 0;
	provincesDie["浙江"] = 0;
	string targetProvince; 
	string filePath("C:\\Users\\Administrator\\Documents\\GitHub\\221701335\\example\\log");
	string outPath;
	string file;
	string date("2020-01-29");
	vector<string> files;
	string format = "";	//.txt
	getAllFiles(filePath, files, format);
	int size = files.size();
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
			option = argv[++i];
		}
		else if(option == "-province"){
			;
		}
		else{
			cout<<"输出参数错误"<<endl;
			return -1;
		}
	}
	
	if(date.length() != 0){
		string dateTemp = date;
		date = filePath.append("\\");
		date.append(dateTemp);
		date.append(".log.txt");
	}
	
	/*
	//测试用：输出日期 
	cout<<endl;
	cout<<"date:"<<endl;
	cout<<date<<endl;
	cout<<"___________________________________________"<<endl;
	*/
	
	for (int i = 0; i<size; i++){	
		if(date.length() != 0){
			if(files[i] > date)
				continue;		
		}
		//cout << files[i] << " :" <<endl;
		char *filepath = const_cast<char *>(files[i].c_str()) ;
		//cout << filepath << " :" <<endl;
		ifstream fin(filepath);
		//处理文档内容
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
			
			if(info == "排除"){
				fin >> temp;
				fin >> numTemp;
				fin >> temp;
				provincesUndef.at(targetProvince) -= numTemp;
				provincesUndef.at("全国") -= numTemp;
			}
			
			else if(info == "死亡"){
				fin >> numTemp;
				fin >> temp;
				provincesDie.at(targetProvince) += numTemp;
				provincesDie.at("全国") += numTemp;
				provincesDef.at(targetProvince) -= numTemp;
				provincesDef.at("全国") -= numTemp;
			}
			
			else if(info == "治愈"){
				fin >> numTemp;
				fin >> temp;
				provincesCure.at(targetProvince) += numTemp;
				provincesCure.at("全国") += numTemp;
				provincesDef.at(targetProvince) -= numTemp;
				provincesDef.at("全国") -= numTemp;
			}
			
			else if(info == "新增"){
				fin >> temp;
				info = Utf8ToAnsi(temp);
				if(info == "感染患者") {
					fin >> numTemp;
					fin >> temp;
					provincesDef.at(targetProvince) += numTemp;
					provincesDef.at("全国") += numTemp;
				} 
				else if(info == "疑似患者"){
					fin >> numTemp;
					fin >> temp;
					provincesUndef.at(targetProvince) += numTemp;
					provincesUndef.at("全国") += numTemp;
				} 
				else{
					cout << targetProvince << "相关文档数据错误" << endl;
					fin.getline(temp,255);
					continue;
				} 
			}
			
			else if(info == "感染患者"){
				fin >> temp;
				fin >> temp; 
				string tempProvince = Utf8ToAnsi(temp);
				fin >> numTemp;
				fin >> temp;
				provincesDef.at(targetProvince) -= numTemp;
				provincesDef.at(tempProvince) += numTemp;
			}
			
			else if(info == "疑似患者"){
				fin >> temp;
				info = Utf8ToAnsi(temp);
				if(info == "确诊感染"){
					fin >> numTemp;
					fin >> temp;
					provincesDef.at(targetProvince) += numTemp;
					provincesDef.at("全国") += numTemp;
					provincesUndef.at(targetProvince) -= numTemp;
					provincesUndef.at("全国") -= numTemp;
				}
				else if(info == "流入"){
					fin >> temp; 
					string tempProvince = Utf8ToAnsi(temp);
					fin >> numTemp;
					fin >> temp;
					provincesUndef.at(targetProvince) -= numTemp;
					provincesUndef.at(tempProvince) += numTemp;
				}
				else{
					cout << targetProvince<<"相关文档数据错误"<<endl;
					fin.getline(temp,255);
					continue; 
				} 	
			}
			
			else{
				cout << targetProvince<<"相关文档数据错误"<<endl;
				fin.getline(temp,255);
				continue; 
			} 
		}
		//当个文档处理完毕 
	}
	//所有指定文档处理完毕
	
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
