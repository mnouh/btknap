/* 
 * File:   Knapsack.cpp
 * Author: mnouh
 * 
 * Created on March 11, 2012, 6:05 PM
 */

#include "Knapsack.h"


Knapsack::Knapsack() {
    
    
    
}

Knapsack::Knapsack(vector< pair<int, int> > problems, int &knapsack_weight, int &numItems, int &problem_Num, int improve, ofstream & output) 
{
    this->MAX_WEIGHT = knapsack_weight;
    this->num_items = numItems;
    this->problem_Num = problem_Num;
    this->items = &problems;
    this->MAX_VALUE = improve;
    
    //cout << "Improved from Greedy: " << improve << endl;
    
    //cout << "Problem #: " << problem_Num << " Number of Items: " <<  numItems << " Maximum Amount of Weight: " << this->MAX_WEIGHT << endl;
    
    //cout << "THE SORTED ITEMS" << endl;
    /*
    for(std::vector< pair<int, int> >::iterator it = this->items->begin(); it != this->items->end(); ++it) {
             
        
       // cout << "First Item: " << it->first << endl;
        cout << "Item " << it->second << endl;
     }
    **/
    //cout << "STARTING TO CALL SOLUTION" << endl;
    
    vector< pair<int, int> > empty;
    this->instance_list = new vector< vector < pair <int, int> > * >;
    
    this->sack(0, 0, 0, empty);
    
    
    /*for(std::vector< pair<int, int> >::iterator it = this->solution->begin(); it != this->solution->end(); ++it) {
             
        
        cout << "Weight: " << it->first << endl;
        cout << "Item Profit " << it->second << endl;
     }
    **/
    //cout << "MAX PROFIT: " << this->MAX_VALUE << endl;
    
    output << num_items << " " << this->MAX_VALUE << " ";
}


void Knapsack::sack(int index, double currentWeight, double currentValue, vector< pair<int, int> > & copiedVector) 
{
    
 if(currentWeight <= this->MAX_WEIGHT && currentValue > this->MAX_VALUE) {
     
     this->MAX_VALUE = currentValue;
     //cout << "MAX profit" << this->MAX_VALUE << endl;
     //this->solution = new vector< pair<int, int> > (copiedVector);
     
 }
 
 
        
 if(promising(index, currentWeight, currentValue)) 
 {
    
     vector< pair<int, int> > * leftNodes = new vector< pair<int, int> > (copiedVector);
     
     pair <int, int> an_item;
     an_item = make_pair(this->items->at(index+1).first, this->items->at(index+1).second);
     leftNodes->push_back(an_item);
     this->instance_list->push_back(leftNodes);
     sack(index+1, currentWeight+this->items->at(index+1).first, currentValue+this->items->at(index+1).second, *leftNodes);
     
     vector< pair<int, int> > * rightNodes = new vector< pair<int, int> > (copiedVector);
     this->instance_list->push_back(rightNodes);
     sack(index+1, currentWeight, currentValue, *rightNodes);
     
 }
 
    
    
}

bool Knapsack::promising(int i, double weight, double value) 
{
    
    double bound = value;
    double size = weight;
    
    int index = i+1;
    
    if(weight >= this->MAX_WEIGHT)
        return false;
    
    while(index < this->items->size() && (size + this->items->at(index).first) <= this->MAX_WEIGHT) {
        size += this->items->at(index).first;
        bound += this->items->at(index).second;
        index++;
        
    }
    
    if(index < this->items->size()) {
        
        bound += (this->MAX_WEIGHT - size) * (this->items->at(index).second/this->items->at(index).first);
    }
    //cout << "Index:" << i << " Bound: " <<  bound << endl;
    return bound > this->MAX_VALUE;
    
    
}

Knapsack::~Knapsack() 
{
    
    for(std::vector< vector < pair <int, int> > * >::iterator it = this->instance_list->begin(); it != this->instance_list->end(); ++it) {
                 
        delete * it;
    
     }
    
    delete this->instance_list;
    
    
}

