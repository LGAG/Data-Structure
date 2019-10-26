    /* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
     
    #include <stdio.h>  
    #include <stdlib.h>  
      
    typedef struct sdata  
    {  char  data;  
       struct sdata *next;  
    } SNODE;  
      
    void setlink( SNODE *, char * ), outlink( SNODE * );  
    int listlen( SNODE * );  
    SNODE * ziplist( SNODE *, SNODE * );  
    SNODE * findlist( SNODE *, SNODE * );  
      
    int main( )  
    {   SNODE * head1, * head2, *head;  
        char str1[100], str2[100];  
      
        gets( str1 );  
        gets( str2 );  
      
        head1 = (SNODE *) malloc( sizeof(SNODE) );  
        head2 = (SNODE *) malloc( sizeof(SNODE) );  
        head = (SNODE *) malloc( sizeof(SNODE) );  
        head->next = head1->next = head2->next = NULL;  
      
        setlink( head1, str1 );  
        setlink( head2, str2);  
      
        head->next = ziplist( head1, head2 );  
      
        head->next = findlist( head1, head2 );  
        outlink( head );  
        return 0;  
    }  
      
    void setlink( SNODE *head, char *str )  
    {  
        SNODE *p ;  
      
        while ( *str != '\0' )  
        {   p  = ( SNODE * ) malloc( sizeof( SNODE ) );  
            p->data = *str;  
            p->next = NULL;  
            str++;  
            head->next = p;  
            head = p;  
        }  
        return;  
    }  
      
    void outlink( SNODE * head )  
    {   while ( head->next != NULL )  
        {  
            printf( "%c", head -> next -> data );  
            head = head -> next;  
        }  
        printf("\n");  
        return;  
    }  
      
    int listlen( SNODE * head )  
    {  
        int len=0;  
        while ( head->next != NULL )  
        {  
            len ++;  
            head = head->next;  
        }  
        return len;  
    }  
      
    SNODE * findlist( SNODE * head1, SNODE * head2 )  
    {  
        int m, n;  
        SNODE *p1=head1, *p2=head2;  
      
        m = listlen( head1 );  
        n = listlen( head2 );  
        while  ( m > n )  
        {   p1 = p1->next;  
            m--;  
        }  
        while  ( m < n )  
        {   p2 = p2->next;  
            n--;  
        }  
      
        while( p1->next != NULL && p1->next != p2->next )  
        {  
            p1 = p1->next;  
            p2 = p2->next;  
        }  
        return p1->next;  
    }  
    
    SNODE * ziplist( SNODE * head1, SNODE * head2 )   
          {   
                SNODE *p1=head1,*p2=head2,*P1=head1,*P2=head2;  
                int len1=listlen(head1),len2=listlen(head2);  
                SNODE *p=NULL;  
                int index=0,len=0,l=0;;  
                if(len1>=len2){  
                    for(int i=0;i<len1-len2;i++){  
                        p1=p1->next;  
                    }  
                    while(p1->next!=NULL&&p2->next!=NULL){  
                        if(index==0){  
                            if(p1->next->data==p2->next->data){  
                                index=1;  
                                len+=l;  
                            /// p=p1;  
                            }  
                            else{  
                                p=p1->next;  
                                len++;  
                            }   
                                p1=p1->next;  
                                p2=p2->next;  
                        }  
                        else if(index==1){  
                            if(p1->next->data!=p2->next->data){  
                                p=p1->next;  
                                index=0;  
                                l=0;  
                                len++;  
                            }  
                                l++;  
                                p1=p1->next;  
                                p2=p2->next;  
                        }  
                    }  
                }  
                else if(len2>len1){  
                    for(int i=0;i<len2-len1;i++){  
                        p2=p2->next;  
                    }  
                    while(p1->next!=NULL&&p2->next!=NULL){  
                        if(index==0){  
                            if(p1->next->data==p2->next->data){  
                                index=1;  
                                len+=l;  
                            /// p=p1;  
                            }  
                            else{  
                                p=p1->next;  
                                len++;  
                            }   
                                p1=p1->next;  
                                p2=p2->next;  
                        }  
                        else if(index==1){  
                            if(p1->next->data!=p2->next->data){  
                                p=p1->next;  
                                index=0;  
                                l=0;  
                                len++;  
                            }  
                                l++;  
                                p1=p1->next;  
                                p2=p2->next;  
                        }  
                    }  
                }  
                if(index==0) return NULL;  
            if(len1>=len2){  
                for(int i=1;i<=len1-len2+len;i++) head1=head1->next;  
                for(int i=0;i<len;i++) head2=head2->next;  
            }  
            else{  
                for(int i=1;i<=len2-len1+len;i++) head2=head2->next;  
                for(int i=0;i<len;i++) head1=head1->next;  
            }  
            head1->next=head2->next;  
                return p;  
          }   
