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
template <class List_entry>
Error_code join(List<List_entry>& list1, List<List_entry>& list2);
template <class List_entry>
void reverse(List< List_entry>& a_list);



int main() {
	//List<int> oscar;
	List<int> Eric;
	List<int> Oscar;

    
	insert_first(69, Eric);
	insert_first(420, Oscar);

	
	cout << " check";
	Eric.traverse(0, 1);

	Oscar.traverse(0, 1);

	cout << endl;

	

	Eric + Oscar;

	cout << endl << "post addition";


	Eric.reverse();
	cout << endl << "post reverse";


	Eric.traverse(0, 2);
	cout << endl << "post transverse";

	

	//Eric.traverse(0, 3);

}

template <class List_entry>
void reverse(List< List_entry>& a_list) 
//reverses the order of all entries in a_list.
{
	a_list.reverse();
}

template <class List_entry>
Error_code join(List<List_entry>& list1, List<List_entry>& list2)
//copies all entries from list1 onto the end of list2;
//list1 remains unchanged, as do all the entries previously in list2.
{
	list2 + list1;
}

template <class List_entry>
Error_code copy(List<List_entry>& dest, List<List_entry>& source)
/*copies all entries from source into dest;
source remains unchanged.You may assume that dest already exists, but any
entries already in dest are to be discarded.
*/ 
{
	dest = source;
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
	cout << "insert first";
    return a_list.insert(0, x);
}