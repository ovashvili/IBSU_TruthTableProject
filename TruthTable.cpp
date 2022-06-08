#include<bits/stdc++.h>

using namespace std;
map<string, string> simpledEquation;

 bool calculate(char exp,bool first, bool second){
 	switch(exp){
 		case '&':
 		return first&&second;
 		
 		case '|':
 		return first||second;
 		
 		case '>':
 		return !(second == false && first == true);
 		
 		case '-':
 		return second == first;
 	}
 		
 		
 }
 
 bool getExp(string exp, bool P, bool Q){
  	
  		bool ans;

 		if(exp[1] == 'p'){
 			ans = calculate(exp[2],P,Q);
 		}
 		else{
 			ans = calculate(exp[2],Q,P);
 		}
		
		simpledEquation[exp] =  ans == true?"t":"f";
		return ans;
 }



void print(	vector<string> simpEquations, vector<string> expressions, bool p, bool q)
{
	for(auto it: simpEquations)
	{
		getExp(it,p,q);
	}
	
	cout << "\n" << (p ? "t" : "f") << "\t" <<  (q ? "t" : "f") << "\t";
	for(int it = 0;it<expressions.size();it++){
		for(auto temp: simpledEquation){
				size_t index = expressions[it].find(temp.first);
				while( index != std::string::npos)
			    {
			        
			        expressions[it] = expressions[it].replace(index,temp.first.length(),temp.second);
			        
			       index = expressions[it].find(temp.first);
			    }
			
		}
	}
	
	for(auto it: expressions){
	
		cout<<it<<"\t";
	}
}

int main()
{
	int N,i,len,k;
	string exp,op;
	string f[100];
	
	vector<string> simpEquations;
	vector<string> expressions;
	cin>>N;
	while(N--)
	{
		k=0;
		cin>>exp;
		exp.push_back(')');
		exp.insert(0,"(");
		len = exp.length();
		int iterator = 0;
		for(i=0; i<len; i++)
		{
			if(exp[i]>='a' && exp[i]<='z')
				f[iterator++] = exp[i];
			else if(exp[i] == '~')
				f[iterator++] = exp[i] + exp[++i];
			else if(exp[i]==')'){
				f[iterator++] = op[--k];
			}
			else if(exp[i]!='(')
				op[k++]=exp[i];
		}
		
		for(int i = 0;i<iterator;i++){
			cout<<f[i];
		}
		cout<<endl;
		
		// 		cout<<endl;
		for(i=0; i < iterator;i++)
		{
			if(f[i] < "a" || f[i]>"z")
			{
				string expression,first,second,lastExpression;
				
				expression = f[i];
				second = f[i-1];
				f[i-1] = "";
		
				
				for(int ind = i-2; ind>=0;ind--)
				{
					if(f[ind] != ""){
						first = f[ind];
						f[ind] = "";
						break;
					}
				}
				lastExpression = "(" + first + expression + second + ")";
				
				f[i] = lastExpression;
				
				
				if(second[second.length()-1] != ')') simpEquations.push_back(lastExpression);
				expressions.push_back(lastExpression);
			}
		}
		
		cout << "p\tq\t";
		for(auto it: expressions)
		{
			cout<<it<<"\t";
		}
		
		print(simpEquations, expressions, true, true);		
		print(simpEquations, expressions, true, false);
		print(simpEquations, expressions, false, true);
		print(simpEquations, expressions, false, false);
		cout << "\n\n";
		expressions.clear();
		simpEquations.clear();
		simpledEquation.clear();
	}
	
	return 0;
}