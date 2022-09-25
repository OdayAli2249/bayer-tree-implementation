#include<iostream>

using namespace std;


struct Node{

int Elem[3];
int si;
struct Node *NodePtr[4];

};

struct Operation{

int OperationID;
int Value;

};

struct Node *AddElem(struct Node *n,int val);
bool SearchElem(int val);
void DisplayTree(struct Node *n);
bool FindForDelete(int val);
void Delete(struct Node *n,int L);
void Call(int ID,int val);
void Free(struct Node *n);

int Found(int Arr[],int S,int val);
bool Place(int S);
int Next(int Arr[],int val);
void AddElemToArr(int Arr[],int S,int val);



struct Node *Root = NULL;
bool Added = false;




int main(){


  int OperationsNumber;
  string OperationType;
  int val;

   cin >> OperationsNumber;
   struct Operation OP[OperationsNumber];


   for(int i = 0 ; i<OperationsNumber ; i++){

       cin >> OperationType;
       cin >> val ;
       if(OperationType == "add"){

              OP[i].OperationID = 1;
              OP[i].Value = val;

       }else if(OperationType == "delete"){
              OP[i].OperationID = 2;
              OP[i].Value = val;

       }else if(OperationType == "search"){
              OP[i].OperationID = 3;
              OP[i].Value = val;

       }



}

 for(int i = 0 ; i<OperationsNumber ; i++){

      Call(OP[i].OperationID,OP[i].Value);

 }


return 0;

}

struct Node *AddElem(struct Node *temp,int val){



     int next;


          if(temp == NULL){

              temp = new struct Node;
              temp->Elem[0] = val;
              temp->si = 1;
              for(int i = 0 ; i<4 ; i++)
                temp->NodePtr[i] = NULL;
                if(Root == NULL){
                    Root = temp;

                }
              Added = true;
              return temp;

          }else if(Found(temp->Elem,temp->si,val) != -1){
              Added = false;

              return NULL;

          }else if(Place(temp->si)){

              AddElemToArr(temp->Elem,temp->si,val);
              if(temp->Elem[0] == val){
                    for(int i = 3 ; i>0 ; i--){
                        temp->NodePtr[i] = temp->NodePtr[i-1];
                    }
                    temp->NodePtr[0] == NULL;
               }else if(temp->Elem[1] == val){
                     temp->NodePtr[3] = temp->NodePtr[2];
                     temp->NodePtr[2] = temp->NodePtr[1];
                     temp->NodePtr[1] = NULL;

               }


              (temp->si)++;
              Added = true;
              return NULL;
          }else{

               next = Next(temp->Elem,val);
              struct Node *C = AddElem(temp->NodePtr[next],val);
             if(C != NULL){

                  temp->NodePtr[next] = C;

             }
             return NULL;

          }

}

int Found(int Arr[],int S,int val){

   for(int i = 0 ; i<S ; i++)
        if(Arr[i] == val)
        return i;
   return -1;

}

bool Place(int S){

     return S != 3;

}

int Next(int Arr[],int val){

        if(val < Arr[0])
              return 0;
        else if(Arr[0] < val && val < Arr[1])
              return 1;
        else if(Arr[1] < val && val < Arr[2])
              return 2;
        else if(Arr[2] < val)
              return 3;

}


void AddElemToArr(int Arr[],int S,int val){

     int i = S-1;
     int k = S;
     while(i+1 != 0)
        if(Arr[i] > val){

            Arr[i+1] = Arr[i];
            k = i;
            i--;

        }else break;


     Arr[k] = val;

}




bool SearchElem(int val){

     struct Node *temp = Root;
     int next;

     do{
            if(temp == NULL)
                return false;
            else if(Found(temp->Elem,temp->si,val) != -1)
                return true;
            else{
                    next = Next(temp->Elem,val);
                    temp = temp->NodePtr[next];
            }


     }while(true);

}



void DisplayTree(struct Node *n){
    if(n == NULL)
        return;


    if(n != NULL){
    for(int i = 0 ; i<n->si ; i++){
    cout << endl << n->Elem[i];
       }
    cout << endl;
    }
    else return;

     for(int i = 0 ; i<4 ; i++)
        DisplayTree(n->NodePtr[i]);

}



bool FindForDelete(int val){

     struct Node *temp = Root;
     int next;
     int Loc;

     do{
            if(temp == NULL)
                return false;
            else if(Found(temp->Elem,temp->si,val) != -1){
                Loc = Found(temp->Elem,temp->si,val);
                Delete(temp,Loc);
                return true;
            }
            else {
                    next = Next(temp->Elem,val);
                    temp = temp->NodePtr[next];
            }


     }while(true);

}



void Delete(struct Node *n,int L){

    struct Node *temp = NULL;
    struct Node *previous = NULL;

     if(n->NodePtr[L] != NULL){
                               /// LEFT

        temp = n->NodePtr[L];


           while(temp->NodePtr[(temp->si)] != NULL){

            temp = temp->NodePtr[(temp->si)];
           }

           n->Elem[L] = temp->Elem[(temp->si)-1];

           Delete(temp,(temp->si)-1);



     }else if(n->NodePtr[L+1] != NULL){
                                     /// RIGHT

           temp = n->NodePtr[L+1];
           while(temp->NodePtr[0] != NULL){
            temp = temp->NodePtr[0];
           }

           n->Elem[L] = temp->Elem[0];
           Delete(temp,0);



     }else{



        for(int i = L ; i<(n->si)-1 ; i++){

            n->Elem[i] = n->Elem[i+1];

            n->NodePtr[i] = n->NodePtr[i+1];
            n->NodePtr[i+1] = n->NodePtr[i+2];
           }

            n->NodePtr[n->si] = NULL;

            (n->si)--;
            if(n->si == 0)
                delete n;

     }


}


void Free(struct Node *n){

if(n == NULL)
    return;
else{
    for(int i = 0 ; i<4 ; i++)
 if(n->NodePtr[i] != NULL){

     if(n->NodePtr[i]->si == 0){
        n->NodePtr[i] = NULL;
     }else Free(n->NodePtr[i]);

    }
  }
}



void Call(int ID,int val){

     if(ID == 1){
        AddElem(Root,val);
        if(Added)
            cout << endl << "ADDED";
        else cout << endl << "ALREADY ADDED";

     }else if(ID == 2){
         Free(Root);
         if(FindForDelete(val))
            cout << endl << "DELETED";
         else cout << endl << "NOT FOUND";
     }else if(ID == 3){
         if(SearchElem(val))
            cout << endl << "FOUND";
            else cout << endl << "NOT FOUND";

     }

}
