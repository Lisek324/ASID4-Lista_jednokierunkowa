#include <iostream>


struct element {
    int data;
    struct element* nextElement;
};

void pushFront(element** head, int number) {
    element* currentElement = new element;              //inicjacja nowego wskaźnika struktury typu 'element' do pustej komórki pamięci
    currentElement->data = number;                      //do nowej struktury przypisz 'number' do właściwości 'data'
    currentElement->nextElement = (*head);              //wskaż na adres pamięci początku listy
    *head = currentElement;                             //przypisz adres nowej komórki do adresu początku listy
}
void pushBack(element**head, int number) {
    if (*head == NULL)
    {
        *head = new element;                            //inicjacja struktury typu 'element' w miejscu pamięci 'head'
        (*head)->data = number;                         //przypisanie cyfry do 'head'
        (*head)->nextElement = NULL;                    //wskazanie następnej komórki na adres o pustej pamięci
    }
    else
    {
        element* currentElement = *head;                //zmienna 'currentElement' wskazująca na pierwszy element w liście
        while (currentElement->nextElement != NULL)     
        {
            currentElement=currentElement->nextElement; //przechodź po liście tak długo, aż następna komórka nie będzie pusta
        }
        currentElement->nextElement = new element;      //zainicjuj do pustej komórki pamięci strukturę typu 'element'
        currentElement->nextElement->data = number;     //do nowej struktury przypisz 'number' do właściwości 'data
        currentElement->nextElement->nextElement = NULL;//połącz nową komórkę z pustą komórką
    }
}
void showList(element *head) {

    if (head == NULL) {
        std::cout << "Empty list";
    }
    else {
        element* currentElement = head;                 //przypisz pierwszy element listy do pomocniczego wskaźnika
        while (currentElement != NULL) {
            std::cout << currentElement->data<<" ";     //pomocniczym wskaźnikiem wypisz wartość na którą wskazuje wskaźnik
            currentElement=currentElement->nextElement; //przesuwaj wskaźnik o następnę miejsce w pamięci
        }
        std::cout << "\n";
    }
}
int listSize(element *head) {
    int c = 0;                                          //wielkość listy
    if (head == NULL) {                                 //jeśli początek listy jest pustą komórką pamięci zwróć wielkość listy 0
        return 0;
    }
    else {
        element* currentElement = head;                 //przypisz pierwszy element listy do pomocniczego wskaźnika
        while (currentElement != NULL) {                //wykonuj tak długo aż wskaźnik pomocniczy nie będzie pusty
            c++;
            currentElement=currentElement->nextElement; //przesuwaj wskaźnik o następnę miejsce w pamięci
        }
        return c;                                       //zwróć wielkość listy
    }
}
void pushByIndex(element** head, int number, int index) {
    if (index == 0) pushFront(head, number);            //wypchnij element na pierwsze miejsce w liście
    else
    {
        if (index == listSize(*head)) pushBack(head, number);//wypchnij element na ostatnie miejsce w liście
        else
        {
            element* currentElement = *head;            //przypisz pierwszy element listy do pomocniczego wskaźnika
            element* tmp;                               //wskaźnik tymczasowy

            int i = 0;
            while (currentElement->nextElement != NULL && i < index - 1)//wykonuj tak długo aż currentElement nie napotka pustej pamięci oraz index-1 jest mniejszy od i
            {
                currentElement = currentElement->nextElement;//przesuń na następną komórkę
                i++;
            }

            tmp = currentElement->nextElement;          //zapisz miejsce pustej komórki do zmiennej tmp
            currentElement->nextElement = new element;  //do pustej komórki stwórz zainicjuj strukturę
            currentElement->nextElement->data = number; //przypisz 'number' do 'data'
            currentElement->nextElement->nextElement = tmp;//od nowej komórki wskaż na komórkę zapisaną w tmp
        }
    }
}
void popFront(element** head) {
    element* tmp = NULL;
    if (*head != NULL) {
        tmp = (*head)->nextElement;                     //zapisz następną komórkę do tmp

        delete* head;                                   //usuń wskaźnik wskazujący na pamięć, która jest początkiem listy
        *head = tmp;                                    //przypisz pamięć ze wskaźnika 'tmp' do wskaźnika 'head'
    }
}
void popBack(element** head) {
    if (*head != NULL) {
        if ((*head)->nextElement == NULL)               //jeśli lista składa się z jednego elementu
        {
            *head = NULL;                               //wskaźnik wskazujący na początek listy wskaż na puste miejsce
        }
        else
        {
            element* currentElement = *head;            //przypisz pierwszy element listy do pomocniczego wskaźnika
            while (currentElement->nextElement->nextElement != NULL)//wykonuj tak długo aż currentElement wskaże na komórkę, która wskaże na komórkę, która nie będzie pusta(druga komórka nie będzie pusta)
            {
                currentElement = currentElement->nextElement;//przesuń o następną komórkę
            }
            delete currentElement->nextElement;         //usuń wskaźnik na następną komórkę

            currentElement->nextElement = NULL;         //wskaż na następne miejsce komórki i przypisz jej miejsce puste
        }
    }
}
void popByIndex(element** head,int index) {
    if (index == 0) {
        popFront(head);
    }
    else {
        element* currentElement = *head;                //przypisz pierwszy element listy do pomocniczego wskaźnika
        element* tmp;

        int i = 0;
        while (currentElement->nextElement != NULL && i < index - 1) {//wykonuj tak długo aż currentElement odwołująca się do następnej komórki nie będzie pusta oraz index-1 jest mniejszy od i
            currentElement = currentElement->nextElement;//przesuń o następną komórkę
            i++;
        }
        tmp = currentElement->nextElement;                  //do wskaźnika tymczasowego przypisz następną komórkę
        currentElement->nextElement = tmp->nextElement;     //do wskaźnika wskazującego na następną komórkę, przypisz wskaźnik tmp wskazujący na następną komórkę
        delete tmp;                                         //usuń wkaźnik wskazujący na pamięć w tmp
    }
}
int main()
{
    element* head = NULL;                           //wskaźnik wskazujący na początek listy
    int action = -1;                                //numer akcji podany przez uzytkownika
    int num = -1;                                   //cyfra podany przez użytkownika
    int indx = -1;                                  //indeks listy

    while (true) 
    {
        std::cout << "Elements in list: ";
        showList(head);
        std::cout << "\n";

        std::cout << "0.Exit program\n";
        std::cout << "1.Push an item to the head of the list\n";
        std::cout << "2.Push an item to the tail of the list\n";
        std::cout << "3.Push an item to specific index of the list\n";
        std::cout << "4.Pop an item from the head of the list\n";
        std::cout << "5.Pop an item from the tail of the list\n";
        std::cout << "6.Pop an item from specific index of the list\n";
        std::cin >> action;

        switch (action)
        {
        case 0:
            return 0;
            break;
        case 1:
            std::cout << "Type a number ";
            std::cin >> num;
            pushFront(&head, num);
            break;
        case 2:
            std::cout << "Type a number ";
            std::cin >> num;
            pushBack(&head, num);
            break;
        case 3:
            std::cout << "Type a number ";
            std::cin >> num;
            std::cout << "Type an index ";
            std::cin >> indx;
            pushByIndex(&head, num, indx);
            break;
        case 4:
            popFront(&head);
            break;
        case 5:
            popBack(&head);
            break;
        case 6:
            std::cout << "Type an index ";
            std::cin >> indx;
            popByIndex(&head,indx);
            break;
        default:
            std::cout << "Invalid action";
            break;
        }
    }
}
