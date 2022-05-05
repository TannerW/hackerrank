#include <bits/stdc++.h>
#include <iostream>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */
 
 // l=m+n
 // o*l = o*(m+n) = o*m+o*n
 void extraLongMult(std::deque<int>* product, int num)
 {
    // std::cout << "num: " << num << std:: endl;
    std::deque<int> orig_copy = *product;
    // std::deque<int> new_prod(1,0);
    int numOrderMag = 1;
    int magCheck = num;
    std::deque<int> num_breakdown;
    while (magCheck/10 != 0)
    {
        numOrderMag++;
        // std::cout << magCheck%10 << std::endl;
        num_breakdown.push_front(magCheck%10);
        magCheck = magCheck/10;
    }
    // std::cout << magCheck%10 << std::endl;
    num_breakdown.push_front(magCheck%10);

    std::deque<int> new_prod((product->size()*2)+1,0);
    
    // std::cout << "magnitude:" << numOrderMag << std::endl;

    deque<int>::reverse_iterator newprod_start_iter = new_prod.rbegin();

    for (int currMag = 0; currMag < numOrderMag; currMag++) //step through numbers of num from 1s place to Ns place
    {
        int currOp = num_breakdown[num_breakdown.size() - currMag - 1]; //current number of num
        // std::cout << "currOp: " << currOp << std::endl;

        for (int prod_itr = product->size()-1; prod_itr >= 0; prod_itr--) //step through numbers of last product from 1s place to Ns place
        {
            int newprod_offset = product->size()-1-prod_itr;
            int newProdVal = product->at(prod_itr)*currOp+*(newprod_start_iter+newprod_offset);
            // std::cout << "prod_itr: " << product->at(prod_itr) << std::endl;
            // std::cout << "newProdVal: " << newProdVal << std::endl;
            
            if (newProdVal >= 10)
            {
                if ((newprod_start_iter+newprod_offset+1) ==  new_prod.rend())
                {
                    // std::cout << "ERROR" << std::endl;
                }
                else
                {
                    *(newprod_start_iter+newprod_offset) = newProdVal%10;
                    
                    int carryOverSum = *(newprod_start_iter+newprod_offset+1) + (newProdVal/10)%10;
                    // std::cout << "carryOverSum: " << carryOverSum << std::endl;
                    *(newprod_start_iter+newprod_offset+1) = carryOverSum%10;
                    if (carryOverSum >= 10)
                    {
                        *(newprod_start_iter+newprod_offset+2) += (carryOverSum/10)%10;
                    }
                }
            }
            else
            {
                *(newprod_start_iter+newprod_offset) = newProdVal%10;
            }

            // std::cout << "newProd: ";
            // bool trunc = true;
            // for (auto val : new_prod)
            // {
            //     if (val != 0)
            //         trunc = false;
            //     if (!trunc)
            //         std::cout << val;
            // }
            // std::cout << std::endl;

        }

        newprod_start_iter++;
    }

    while (new_prod[0] == 0)
    {
        new_prod.pop_front();
    }
    product->swap(new_prod);
 }

void extraLongFactorials(int n) {
    std::deque<int> product(1, 1);
    for (int i = 1; i <= n; i++)
    {
        extraLongMult(&product, i);
        // std::cout << "currProd: ";
        // for (auto val : product)
        // {
        //     std::cout << val;
        // }
        // std::cout << std::endl;
        // std::cout << "========" << std::endl;
    }
    for (auto val : product)
    {
        std::cout << val;
    }
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    extraLongFactorials(n);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
