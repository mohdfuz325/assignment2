#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calculate.h"

struct node {
    int data;
    struct node *next;
}*head1, *head2, *head3;
void insertAtBeg(struct node **head,int val);
void insertAtEnd(struct node** head, int data);
void add(char arr1[],char arr2[],int l1,int l2);
void multiply(char arr1[], char arr2[], int l1, int l2);
void print(struct node *node);
void subtract(char arr1[], char arr2[], int l1, int l2);

void insertAtBeg(struct node **head, int val) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    if (*head == NULL) {
        *head = temp;
        return;
    }
    struct node *node = *head;
    while (node->next != NULL)
        node = node->next;
    node->next = temp;
}
void insertAtEnd(struct node** head, int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void print(struct node *node) {
    while (node != NULL) {
        printf("%d", node->data);
        node = node->next;
    }
    printf("\n");
}

void initialize(char arr1[], char arr2[], int l1, int l2) {
    head1 = NULL;
    head2 = NULL;
    head3 = NULL;

    int i,j;
    for (i = l1 - 1; i >= 0; i--) {
        j=arr1[i]-'0';
        insertAtBeg(&head1, j);
    }
    for (i = l2 - 1; i >= 0; i--) {
         j=arr2[i]-'0';
        insertAtBeg(&head2,j);
    }
    
}

void add(char arr1[],char arr2[],int l1,int l2) {
     initialize(arr1, arr2, l1, l2);
    struct node *temp1 = head1;
    struct node *temp2 = head2;
    struct node *temp3 = NULL;
    int carry = 0;

    while (temp1 != NULL || temp2 != NULL) {
        int val1,val2;
        if(temp1!=NULL)
        val1=temp1->data;
        else 
        val1=0;
       if(temp2!=NULL)
        val2=temp2->data;
        else 
        val2=0;
        int sum = val1 + val2 + carry;
        carry = sum / 10;
        insertAtBeg(&head3, (sum % 10));
        if (temp1 != NULL) temp1 = temp1->next;
        if (temp2 != NULL) temp2 = temp2->next;
    }

    if (carry > 0) {
        insertAtBeg(&head3, carry );
    }
    printf("Result of addition: \n");
    print(head3);
}
void subtract(char arr1[], char arr2[], int l1, int l2) {
    initialize(arr1, arr2, l1, l2);
    struct node *temp1 = head1;
    struct node *temp2 = head2;
    struct node *temp3 = NULL;
    int borrow = 0;

    while (temp1 != NULL || temp2 != NULL) {
        int val1 = (temp1 != NULL) ? temp1->data : 0;
        int val2 = (temp2 != NULL) ? temp2->data : 0;
        int diff = val1 - val2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insertAtBeg(&head3, diff);

        if (temp1 != NULL) temp1 = temp1->next;
        if (temp2 != NULL) temp2 = temp2->next;
    }
    printf("Result of subtraction: \n");
    print(head3);
}
void multiply(char arr1[], char arr2[], int l1, int l2) {
    int resultLength = l1 + l2;
    int result[resultLength];
    
    for (int i = 0; i < resultLength; i++) {
        result[i] = 0;
    }

    for (int i = l1 - 1; i >= 0; i--) {
        for (int j = l2 - 1; j >= 0; j--) {
            int digit1 = arr1[i] - '0';
            int digit2 = arr2[j] - '0';
            int product = digit1 * digit2;
            result[i + j + 1] += product;
        }
    }

    for (int i = resultLength - 1; i > 0; i--) {
        result[i - 1] += result[i] / 10;
        result[i] = result[i] % 10;
    }

    head3 = NULL;

    for (int i = 0; i < resultLength; i++) {
        insertAtBeg(&head3, result[i]);
    }

    struct node *node;
    while(head3!=NULL)
    {
        insertAtBeg(&node,head3->data);
        head3=head3->next;
    }
        
    printf("Result of multiplication: ");
    print(node);
}

void  divideNumbers(char input[], int divisor) {
    struct node* dividend = NULL;
   

    for (int i = 0; input[i] != '\0'; i++) {
        insertAtEnd(&dividend, input[i] - '0');
    }

    if (divisor == 0) {
        printf("Division by zero is not allowed.\n");
        return;
    }

    struct node* quotient = NULL;
    int carry = 0;

    while (dividend != NULL) {
        int currentDigit = dividend->data + carry * 10;
        carry = currentDigit % divisor;
        currentDigit /= divisor;
        insertAtEnd(&quotient, currentDigit);
        dividend = dividend->next;
    }

    if (quotient == NULL) {
        insertAtEnd(&quotient, 0);
    }
    if (quotient != NULL) {
        printf("Quotient: ");
        print(quotient);
    }
    // Free memory used by the linked lists
    while (dividend != NULL) {
        struct node* temp = dividend;
        dividend = dividend->next;
        free(temp);
    }
    while (quotient != NULL) {
        struct node* temp = quotient;
        quotient = quotient->next;
        free(temp);
    }
   
}




