#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <deque>
using namespace std;
int power[16] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
int regi[16] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int hlt_flag=0;
int string_to_int(string s){
    int i=0;
    int val=0;
    while(s[i]!='\0'){
        if(s[i]=='1') val=val+power[s.size()-i-1];
        i++;
    }
  //  cout<<val<<endl;
    return val;
}
int string_to_2comp(string s){
    int x;
    x=string_to_int(s);
    if(s[0]=='1'){
        x=x-power[s.size()];
    }
    return x;
}
string int_to_string(int n){
    string s = "";
    for(int i=0; i<8; i++){
        char c = n%2+48;
        s = c+s;
        n/=2;
    }
    return s;
}
string decode_opcode(string s){
    string x(s,0,4);
    return x;
}
string decode_operand1(string s){
    string x(s,4,4);
    return x;
}
string decode_operand2(string s){
    string x(s,8,4);
    return x;
}
string decode_operand3(string s){
    string x(s,12,4);
    return x;
}
string decode_operand4(string s){
    string x(s,4,8);
    return x;
}
string decode_operand5(string s){
    string x(s,8,8);
    return x;
}
string fetch(vector<string> v,int &pc){
    string s;
    s=v[pc];
    pc++;
    return s;
}
vector<int> decode(string s){
    vector<int> v;
    string Add("0000");
    string sub("0001");
    string Mul("0010");
    string inc("0011");
    string And("0100");
    string Or("0101");
    string Not("0110");
    string Xor("0111");
    string load("1000");
    string store("1001");
    string jmp("1010");
    string beqz("1011");
    string hlt("1111");
    string w,x,y,z,m,n;
    w=decode_opcode(s);
    x=decode_operand1(s);
    y=decode_operand2(s);
    z=decode_operand3(s);
    m=decode_operand4(s);
    n=decode_operand5(s);
    if(w==Add){
        v.push_back(0);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_int(z);
     /*   cout<<x<<endl;
        cout<<a<<endl;
        cout<<y<<endl;
        cout<<b<<endl;
        cout<<z<<endl;
        cout<<c<<endl;  */
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==sub){
        v.push_back(1);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_int(z);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==Mul){
        v.push_back(2);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_int(z);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==inc){
        v.push_back(3);
        int a;
        a=string_to_int(x);
        v.push_back(a);
        return v;
    }
    else if(w==And){
        v.push_back(4);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_int(z);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==Or){
        v.push_back(5);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_int(z);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==Not){
        v.push_back(6);
        int a,b;
        a=string_to_int(x);
        b=string_to_int(y);
        v.push_back(a);
        v.push_back(b);
        return v;
    }
    else if(w==Xor){
        v.push_back(7);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_int(z);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==load){
        v.push_back(8);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_2comp(z);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==store){
        v.push_back(9);
        int a,b,c;
        a=string_to_int(x);
        b=string_to_int(y);
        c=string_to_2comp(z);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        return v;
    }
    else if(w==jmp){
        v.push_back(10);
        int a;
        a=string_to_2comp(m);
        v.push_back(a);
        return v;
    }
    else if(w==beqz){
        v.push_back(11);
        int a,b;
        a=string_to_int(x);
        b=string_to_2comp(n);
        v.push_back(a);
        v.push_back(b);
        return v;
    }
    else{
        v.push_back(12);
        return v;
    }
}
vector<int> execute_alu(vector<int> v,int &pc){
    int A,B;
    int alu_output=0;
    vector<int> x;
    if(v[0]==0){
  /*      cout<<decoding[1]<<endl;
        cout<<decoding[2]<<endl;
        cout<<decoding[3]<<endl;*/
        alu_output=regi[v[2]]+regi[v[3]];
        A=regi[v[2]];
        B=regi[v[3]];
     /*       cout<<A<<endl;
           cout<<B<<endl; */
    }
        else if(v[0]==1){
            alu_output=regi[v[2]]-regi[v[3]];
            A=regi[v[2]];
            B=regi[v[3]];
        }
        else if(v[0]==2){
            alu_output=regi[v[2]]*regi[v[3]];
            A=regi[v[2]];
            B=regi[v[3]];
        }
        else if(v[0]==3){
            alu_output=regi[v[1]]+1;
            A=regi[v[1]];
            B=0;
        }
        else if(v[0]==4){
            alu_output=regi[v[2]]&regi[v[3]];
            A=regi[v[2]];
            B=regi[v[3]];
         /*   cout<<A<<endl;
            cout<<B<<endl;
            cout<<alu_output<<endl;*/

        }
        else if(v[0]==5){
            alu_output=regi[v[2]]|regi[v[3]];
            A=regi[v[2]];
            B=regi[v[3]];
        }
        else if(v[0]==6){
            alu_output=~regi[v[2]];
            A=regi[v[2]];
            B=0;
        }
        else if(v[0]==7){
            alu_output=regi[v[2]]^regi[v[3]];
            A=regi[v[2]];
            B=regi[v[3]];
        }
        else if(v[0]==8){
            alu_output=regi[v[2]]+v[3];
        }
        else if(v[0]==9){
            B=regi[v[1]];
            alu_output=regi[v[2]]+v[3];
        }
        else if(v[0]==10){
            pc=pc+v[1]-1;
        }
        else if(v[0]==11){
            A=regi[v[1]];
            if(A==0) pc=pc+v[2]-1;
        }
        else{
            hlt_flag=1;
        }
        x.push_back(alu_output);
        x.push_back(v[0]);
        x.push_back(v[1]);
        x.push_back(B);
        return x;
}
vector<int> mem_p(vector<string> &d,vector<int> e){
    int load=0;
    vector<int> x;
    if(e[1]==8){
        load=string_to_int(d[e[0]]);
    }
    if(e[1]==9){
        d[e[0]]=int_to_string(e[3]);
    }
    x.push_back(load);
    x.push_back(e[1]);
    x.push_back(e[2]);
    x.push_back(e[0]);
    return x;
}
void wb(vector<int> m){
    if(m[1]==8){
        regi[m[2]]=m[0];
    }
    if(m[1]<8){
        regi[m[2]]=m[3];    
    }
}
int raw(vector<int>v,vector<int>u,int x){
    if(v[0]<=8){
        if(u[0] == 0 || u[0] == 1 || u[0] == 2 || u[0] == 4 || u[0] == 5 || u[0] == 7){
            if(v[1] == u[2] || v[1] == u[3])return 3-x;
        }
        else if(u[0] == 8 || u[0] == 6){
            if(v[1] == u[2])return 3-x;
        }
        else if(u[0] == 3){
            if(v[1] == u[1])return 3-x;
        }
    }
    return 0;
}
int main(){
    int no_of_inst=0;
    vector<string> vec;
    vector<string> rvec;
    vector<string>::iterator iter;
    string line;
    ifstream fin;
    fin.open("input.txt");
    while (!fin.eof()) {
        getline(fin, line);
      //  string a(line,0,16);
        //string b(line,16,16);
        vec.push_back(line);
    }
    /*
    iter=vec.begin();
    while(iter != vec.end()){
        cout<<*iter<<endl;
        cout<<string_to_int(*iter)<<endl;
        iter++;
    }*/
    fin.close();             //reading instructions from file an placing in a vector

 /*   ifstream fin2;
    int index=0;
    fin2.open("rfile.txt");
    while (!fin2.eof()) {
        getline(fin2, line);
      //  string a(line,0,16);
        //string b(line,16,16);
        rvec.push_back(line);
    }
    iter=rvec.begin();
    while(iter != rvec.end()){
     //   cout<<*iter<<endl;
     //   cout<<string_to_int(*iter)<<endl;
        regi[index]=string_to_int(*iter);
     //   cout<<regi[index]<<endl;
        iter++;
        index++;

    }
    fin2.close();*/
    vector<string> dcache;
    for(int i=0;i<256;i++){
        dcache.push_back("00001111");
    }                        // datacache initialisation
    int cycles=0;
    int stall=0;
    int stall2=0;
    int tot_stall=0;
    int tot_stall2=0;
    int pc=0;
    string IR;
    vector<int> decoding;
    vector<int> executing;
    vector<int> mem;

    deque<vector<int>>ins;
    deque<int>progress;
    int i=0; //remove
    //cout << hlt_flag; //remove
    while(hlt_flag==0){
        // cout << i << endl; //remove
        // i++; //remove
        // cout << hlt_flag << endl; //remove
        cycles++;
        no_of_inst++;
        //fetch
        IR=fetch(vec,pc);
        //decode
        decoding=decode(IR);
        //execute
        executing=execute_alu(decoding,pc);
        //mem
        mem=mem_p(dcache,executing);
        //write back
        wb(mem);
            if(ins.size()){
            stall = raw(ins[ins.size()-1],decoding,1);
            if(stall==0 && ins.size()-1){
                stall = raw(ins[ins.size()-2],decoding,2);
            }
        }
        for(int i=0; i<progress.size(); i++){
            progress[i] = progress[i]+stall;
        }
        cycles+=stall;
        while(progress[0]>=5){
            ins.pop_front();
            progress.pop_front();
        }

        if(decoding[0] == 10 || decoding[0] == 11)stall2 = 2;

        ins.push_back(decoding);
        progress.push_back(1);

        for(int i=0; i<progress.size(); i++){
            progress[i] = progress[i]+stall2;
        }
        cycles+=stall2;
        while(progress[0]>=5){
            ins.pop_front();
            progress.pop_front();
        }
        tot_stall2+=stall2; //remove
        tot_stall+=stall;
        stall2 = 0;
        stall=0;
    } 
  //  cout << tot_stall << " " << tot_stall2 << endl;
  //  cout<<hlt_flag<<endl;
    cout<<"No Of Instructions:"<<no_of_inst<<endl;
    cout<<"No Of Cycles:"<<cycles<<endl;
    cout<<"CPI:"<<cycles/no_of_inst<<endl;
    cout<<"No Of Stalls:"<<tot_stall+tot_stall2<<endl;
    cout<<"No Of RAW Stalls:"<<tot_stall<<endl;
    cout<<"No Of branch Stalls:"<<tot_stall2<<endl;
  //  cout<<string_to_int("0001")<<endl;
    cout<<endl;
    cout<<"Components Of Register:"<<endl;
    for(int i=0;i<16;i++) cout<<"R["<<i<<"]="<<regi[i]<<endl;
    cout<<"Data Cache Contents:"<<endl;
    iter=dcache.begin();
    while(iter != dcache.end()){
        cout<<*iter;
        iter++;
        cout<<*iter;
        iter++;
        cout<<*iter;
        iter++;
        cout<<*iter<<endl;
        iter++;
        
    }
    return 0;
}



