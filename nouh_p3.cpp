#include "Knapsack.h"
#define NUM_PROBLEM 500 //Number of Problems that this program can run.

using namespace std;

struct sort_comp {
    bool operator()(const pair<float,float> &left, const pair<float,float> &right) {
        return (left.second/left.first) < (right.second/right.first);
    }
};


vector< pair<int, int> > greedy(vector< pair<int, int> > * items, int MAX_WEIGHT) {

    int current_weight = 0;
    int current_profit = 0;
    int j = items->size();
    vector< pair<int, int> > knapsack;
    
    while((j != 0) && (current_weight <= MAX_WEIGHT)) {
                
                if((current_weight + items->at(j-1).first) <= MAX_WEIGHT) {
                
                    current_weight = current_weight + items->at(j-1).first;
                    current_profit = current_profit + items->at(j-1).second;    
                    
                }
                
                j--;
                
                
            }
                    pair <int, int> one;
                    one = make_pair(current_weight, current_profit);
                    knapsack.push_back(one);
    
    
    
    return knapsack;
    
    
    
}


int improvedgreedy(vector< pair<int, int> > * items, int greedy_profit, int MAX_WEIGHT) {
 int profit = greedy_profit;   
 int max = items->front().second;
 int j = items->size();
 while(j != 0) {

     if((items->at(j-1).second > max) && (items->at(j-1).first <= MAX_WEIGHT))
            max = items->at(j-1).second;
     if(max > profit)
            return  max;
     else return  profit;
     
     j--;
}    
    
}


int main(int argc, char ** argv) {
        string line;
        string begin;
        string nItems;
        string sMaxWeight;
        vector< pair<int, int> > * weights[NUM_PROBLEM];
        vector< pair<int, int> > * problems[NUM_PROBLEM]; // array of problem vector pointers.
        //map<int, int> * items[500];
        int index = 0;
        
        if(argc != 3) {
            
            cout << "There was a problem with your command line argument inputs" << endl;
            exit(1);
        }
        else {
        
        string inputFile = argv[1];
        string outputFile = argv[2];
        ifstream myfile(inputFile.c_str());
        if (myfile.is_open()) {

            while (myfile.good()) {
                
                getline(myfile, begin);
                if(!myfile.eof()) {
                int pos = begin.find(' ');

                nItems = begin.substr(0, pos + 1);
                begin.erase(0, pos);
                sMaxWeight = begin;

                int numberItems = atoi(nItems.c_str());
                int maxWeight = atoi(sMaxWeight.c_str());


                vector< pair<int, int> > * problemSack = new vector< pair<int, int> > ();
                vector< pair<int, int> > * problemInfo = new vector< pair<int, int> > ();

                pair <int, int> info;
                info = make_pair(numberItems, maxWeight);

                weights[index] = problemInfo;
                problems[index] = problemSack;

                weights[index]->push_back(info);

                for (int i = 0; i < numberItems; i++) {

                    getline(myfile, line);
                    int space = line.find(' ');
                    int weight_i = atoi(line.substr(0, space + 1).c_str());
                    line.erase(0, space);
                    int profit_i = atoi(line.c_str());

                    problems[index] = problemSack;
                    pair <int, int> one;
                    one = make_pair(weight_i, profit_i);
                    problems[index]->push_back(one);
                }
                ++index;
            }
            }
            myfile.close();
        }
        else {
            cerr << "Could not open the file: " << inputFile << endl; 
            exit(1);
        }
        ofstream output;
        output.open(outputFile.c_str());
        
        if(output.is_open()) {
        
        //index = index - 1; //Set the correct number of problems.
            
        //struct timeval start_time, end_time, elapsed_time ;
            
        //time_t start, end;
        for (int z = 0; z < index; z++) { //1 = index; REMEMBER TO SET BACK.

            int MAX_WEIGHT = weights[z]->front().second;
            int n_items = weights[z]->front().first;
            int problem_num = z+1;
            
            
            sort(problems[z]->begin(), problems[z]->end(), sort_comp());
            
            vector< pair<int, int> > item_sorted;
            
            // pair <int, int> dummy;
             //dummy = make_pair(0, 0);
             
             //item_sorted.push_back(dummy);
             
             for(std::vector< pair<int, int> >::iterator it = problems[z]->end(); it >= problems[z]->begin(); --it) {
             
                 pair <int, int> an_item;
                 an_item = make_pair(it->first, it->second);
             
                 item_sorted.push_back(an_item);
             }
            
            clock_t start; //start to time to the function
            double diff;
            start = clock(); //Get the current time
            
            //gettimeofday(&start_time, NULL);
            
            //time (&start);
            
            vector< pair<int, int> > greedyS = greedy(problems[z], MAX_WEIGHT);
            int improved = improvedgreedy(problems[z], greedyS.front().second, MAX_WEIGHT);
            
            
            Knapsack * sack = new Knapsack(item_sorted, MAX_WEIGHT, n_items, problem_num, improved, output);
            
            diff = ( clock() - start ) / (double)CLOCKS_PER_SEC;
            //time (&end);
            //diff = difftime (end,start);
            //gettimeofday(&end_time, NULL);
            
            delete sack;
            
            
            
            //elapsed_time.tv_usec = end_time.tv_usec - start_time.tv_usec;
            
            output.setf(ios::fixed,ios::floatfield);
            output << diff << endl;
            
            //output << n_items << " " << sack.front().second << " " << (elapsed_time.tv_usec) * 0.001 << endl;
            
            /*
            cout << "Problem #: " << problem_num + 1 << endl;
            cout << "Number Items: " << weights[z]->front().first << endl;
            cout << "Maximum Weight: " << weights[z]->front().second << endl;
            cout << "Weight Solution: " << sack.front().first << endl;
            cout << "Profit Solution: " << sack.front().second << endl;
             */
            
            
            
        }
        }
        
        
            for(int j = 0; j < index; j++ ) {
            
            delete problems[j]; // free up memory.
            delete weights[j]; //free up memory
         
            
            }
            
        


        
        
        } 
        
    return 0;
}

