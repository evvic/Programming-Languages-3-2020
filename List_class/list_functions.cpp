#include <iostream>
#include "Utility.h"
#include "List.h"

using namespace std;

template <class List_entry>
Error_code insert_first(const List_entry& x, List<List_entry>& a_list);
template <class List_entry>
Error_code remove_first(List_entry& x, List<List_entry>& a_list);
template <class List_entry>
Error_code insert_last(const List_entry& x, List<List_entry>& a_list);
template <class List_entry>
Error_code remove_last(List_entry& x, List< List_entry>& a_list);
template <class List_entry>
Error_code median_list(List_entry& x, List< List_entry>& a_list);





int main() {
	//List<int> oscar;
	List<int> Eric;
    
	insert_first(69, Eric);
}

template <class List_entry>
Error_code median_list(List_entry& x, List< List_entry>& a_list)
/*
copies the central entry of the
List a_list to x if a_list has an odd number of entries; otherwise, it copies the
left - central entry of a_list to x.
*/
{

}

template <class List_entry>
Error_code remove_last(List_entry& x, List< List_entry>& a_list) 
//removes the last entry of a_list, copying it to x.
{
	return a_list.remove(a_list.getCount(), x);
}

template <class List_entry>
Error_code insert_last(const List_entry& x, List<List_entry>& a_list)
//inserts x as the last entry of the List a_list.
{
	return a_list.insert(a_list.getCount(), x);
}

template <class List_entry>
Error_code remove_first(List_entry& x, List<List_entry>& a_list)
//removes the first entry of the List a_list, copying it to x.
{
	
	return a_list.remove(0, x);
}

template <class List_entry>
Error_code insert_first(const List_entry& x, List<List_entry> &a_list)
//inserts entry x into position 0 of the List a_list.
{
    return a_list.insert(0, x);
}