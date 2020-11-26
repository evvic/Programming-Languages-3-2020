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
Error_code median_list(List_entry& x, List<List_entry>& a_list);
template <class List_entry>
Error_code interchange(int pos1, int pos2, List< List_entry>& a_list);
template <class List_entry>
void reverse_traverse_list(List<List_entry>& a_list, void (*visit)(List_entry&));
template <class List_entry>
Error_code copy(List<List_entry>& dest, List<List_entry>& source);



int main() {
	//List<int> oscar;
	List<int> Eric;
    
	insert_first(69, Eric);
}

template <class List_entry>
Error_code copy(List<List_entry>& dest, List<List_entry>& source)
/*copies all entries from source into dest;
source remains unchanged.You may assume that dest already exists, but any
entries already in dest are to be discarded.
*/ 
{

}

template <class List_entry>
void reverse_traverse_list(List<List_entry>& a_list, void (*visit)(List_entry&)) 
//traverses the List a_list in reverse order(from its last entry to its first).
{
	//                       (start, end)
	return a_list.traverse(0, a_list.getCount());
}


template <class List_entry>
Error_code interchange(int pos1, int pos2, List< List_entry>& a_list)
//interchanges the entries at positions pos1and pos2 of the List a_list.
{
	return a_list.interchange(pos1, pos2);
}

template <class List_entry>
Error_code median_list(List_entry& x, List< List_entry>& a_list)
/*
copies the central entry of the
List a_list to x if a_list has an odd number of entries; otherwise, it copies the
left - central entry of a_list to x.
*/
{
	return a_list.median(x);
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