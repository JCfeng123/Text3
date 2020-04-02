#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
struct Node {
    int coefficent;
    int index;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read();
 
List add(List L1, List L2);
List mul(List L1, List L2);

void Print(List L);
int main()
{
    List S1, S2;
    S1 = Read();
    S2 = Read();
    List S3, S4;
    S3 = add(S2, S1);
    S4 = mul(S2, S1);
    Print(S4);
    Print(S3);
    return 0;
}

List Read() {
    int c, i, n;
    scanf_s("%d", &n);
    List head;
    head = (List)malloc(sizeof(struct Node));
    head->Next = NULL;
    List Ptr = head;
    while (n--) {
        List New= (List)malloc(sizeof(struct Node));
        New->Next = NULL;
        scanf_s("%d %d", &c, &i);
        New->coefficent = c;
        New->index = i;
        Ptr->Next = New;
        Ptr = New;
    }
    head = head->Next;
    return head;
}

List add(List L1, List L2) {
    List head= (List)malloc(sizeof(struct Node));
    head->Next = NULL;
    List Ptr = head;
    while (L1 && L2) {
        List New= (List)malloc(sizeof(struct Node));
        if (L1->index > L2->index) {
            New->coefficent = L1->coefficent;
            New->index = L1->index;
            New->Next = NULL;
            L1 = L1->Next;
        }
        else if (L1->index < L2->index) {
            New->coefficent = L2->coefficent;
            New->index = L2->index;
            New->Next = NULL;
            L2 = L2->Next;
        }
        else if (L1->index == L2->index && L1->coefficent + L2->coefficent == 0) {
            L1 = L1->Next;
            L2 = L2->Next;
            continue;
        }
        else {
            New->coefficent = L1->coefficent+L2->coefficent;
            New->index = L1->index;
            New->Next = NULL;
            L1 = L1->Next;
            L2 = L2->Next;
        }
        Ptr->Next = New;
        Ptr = New;
    }
    while (L1) {
        List New2= (List)malloc(sizeof(struct Node));
        New2->Next = NULL;
        New2->coefficent = L1->coefficent;
        New2->index = L1->index;
        Ptr->Next = New2;
        Ptr = New2;
        L1 = L1->Next;
    }
    while (L2) {
        List New3 = (List)malloc(sizeof(struct Node));
        New3->Next = NULL;
        New3->coefficent = L2->coefficent;
        New3->index = L2->index;
        Ptr->Next = New3;
        Ptr = New3;
        L2 = L2->Next;
    }
    head = head->Next;
    return head;
}

List mul(List L1, List L2) {
    if (!L1 && !L1) { return NULL; }
    List head= (List)malloc(sizeof(struct Node));
    head->Next = NULL;
    List y1 = head, t1 = L1, t2 = L2;
    while (t2) {
        List New1= (List)malloc(sizeof(struct Node));
        New1->Next = NULL;
        New1->coefficent = L1->coefficent * t2->coefficent;
        New1->index = L1->index + t2->index;
        y1->Next = New1;
        y1 = New1;
        t2 = t2->Next;
    }
    t1 = t1->Next;
    while (t1) {
        t2 = L2;
        while (t2) {
            int c, i;
            c = t1->coefficent * t2->coefficent;
            i = t1->index + t2->index;
            List q = head;
            y1 = head->Next;
            while (y1) {
                if (i > y1->index) {
                    List New2= (List)malloc(sizeof(struct Node));
                    New2->Next = NULL;
                    New2->coefficent = c;
                    New2->index = i;
                    New2->Next = y1;
                    q->Next = New2;
                    break;
                }
                else if (i == y1->index) {
                    if (c == y1->coefficent) {
                        q->Next = y1->Next;
                        free(y1);
                        break;
                    }
                    List New2 = (List)malloc(sizeof(struct Node));
                    New2->Next = NULL;
                    New2->coefficent = c + y1->coefficent;
                    New2->index = y1->index;
                    New2->Next = y1->Next;
                    free(y1);
                    q->Next = New2;
                    break;
                }
                else if (y1->Next == NULL) {
                    List New2 = (List)malloc(sizeof(struct Node));
                    New2->Next = NULL;
                    New2->coefficent = c;
                    New2->index = i;
                    y1->Next = New2;
                    break;
                }
                y1 = y1->Next;
                q = q->Next;
            }
            t2 = t2->Next;
        }
        t1 = t1->Next;
    }
    head = head->Next;
    return head;
}

void Print(List L) {
    if (!L) {
        printf("0 0\n");
        return;
    }
    while (L) {
        if (L->Next == NULL) {
            printf("%d %d\n", L->coefficent, L->index);
        }
        else {
            printf("%d %d ", L->coefficent, L->index);
        }
        L = L->Next;
    }
}