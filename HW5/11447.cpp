#include<cassert>
#include<iostream>
#include<map>
#include<string>
#include<cstddef>
namespace oj
{
	struct String
	{
		std::string str;
		String(const std::string &);
		String(const String &);
		String& operator=(const String &);
	};

	std::ostream& operator<<(std::ostream &,const String &);

	void insert(std::map<int,String> &ma,int key,const std::string &str);
	void output(const std::map<int,String> &ma,int begin,int end);
	void erase(std::map<int,String> &ma,int begin,int end);

	std::ostream& operator<<(std::ostream &,const std::map<int,String> &);
}


namespace oj
{
	String::String(const std::string &str_)
		:str(str_){}

	String::String(const String &rhs)
		:str(rhs.str){}

	String& String::operator=(const String &rhs)
	{
		str=rhs.str;
		return *this;
	}

	std::ostream& operator<<(std::ostream &os,const String &str)
	{
		return os<<str.str;
	}
}
int main()
{
	using namespace std;
	using namespace oj;
	map<int,String> ma;
	for(string cmd;cin>>cmd;)
	{
		if(cmd=="insert")
		{
			int key;
			cin>>key>>cmd;
			oj::insert(ma,key,cmd);
		}
		else
			if(cmd=="range")
			{
				int begin,end;
				cin>>cmd>>begin>>end;
				if(cmd=="output")
					output(ma,begin,end);
				else
					if(cmd=="erase")
						erase(ma,begin,end);
					else
						assert(false);
			}
			else
				assert(false);
		cout<<ma<<endl;
	}
}

void oj::insert(std::map<int,oj::String> &ma,int key,const std::string &str){
	if(ma.find(key)!=ma.end()) {
		ma.find(key)->second.str = str + ma.find(key)->second.str;
	}
	else{
		oj::String tmp(str);
		ma.insert(std::make_pair(key, tmp));
	}
}
void oj::output(const std::map<int,oj::String> &ma,int begin,int end){
	auto begin_it = ma.lower_bound(begin);
	if(begin_it==ma.end())return;
	auto end_it = ma.upper_bound(end);
	for(; begin_it!=end_it; begin_it++){
		std::cout<<begin_it->second<<" ";
	}
}
void oj::erase(std::map<int,oj::String> &ma,int begin,int end){
	auto begin_it = ma.lower_bound(begin);
	if(begin_it==ma.end())return;
	auto end_it = ma.upper_bound(end);
	if(begin_it == end_it) return;
	auto tmp = begin_it++;
	for(; begin_it!=end_it; begin_it++){
		ma.erase(tmp);
		tmp = begin_it;
	}
	ma.erase(tmp);
}

std::ostream& oj::operator<<(std::ostream &output,const std::map<int,oj::String> &ma){
	if(ma.empty()) return output;
	for(auto it = ma.begin(); it!= ma.end(); it++) std::cout<<it->second<<" ";
	return output;
}