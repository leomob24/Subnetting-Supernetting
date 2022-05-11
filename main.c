/*programma da eseguire su ambienti linux possibilmente ubuntu*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 32
int classi(int ip[],int ipb[]);
void verifica();
void verifica2(int ip[],int ipb[],int nbitr,int sm,int rbin[],int nib[]);
void supernetting(int ip[],int ipb[],int nbitr,int sm,int rbin[],int nib[]);
void conversione(int ip[],int ipb[]);
void calcolatore(int ip[],int ipb[],int nbitr,int sm,int rbin[],int nib[]);
void netid(int ip[],int ipb[],int nbitr,int nib[],int stamp);
void broad(int ip[],int ipb[],int nbitr,int nib[],int stamp);
void gw(int ip[],int ipb[],int nbitr,int nib[],int stamp);
void range(int ip[],int ipb[],int nbitr,int nib[],int stamp);
void addBinary(int rbin[],int j,int sm,int nbitr,int ipb[],int sum[]);
void addBinary2(int rbin[],int j,int sm,int nbitr,int ipb[],int sum[]);
void subnet(int nbitr);

int main()
{
    int ip[4], ipb[31], ipb2[MAX],sm,nbitr, rbin[7],flag=0,scelta,nib[31];
    do
    {
        printf("\nMenu di scelta\ndigitare 1 per visualizzare classe e verificare se l'indirizzo ip inserito e' privato o pubblico\ndigitare 2 per visualizzare se dati due indirizzi ip e una subnetmask appartengono alla stessa rete\ndigitare 3 per calcolare un numero da inserire di sottoreti dato un indirizzo ip\ndigitare 4 per calcolare un numero da inserire di sottoreti in mashera variabile dato un indirizzo ip e numero degli host per ogni sottorete\ndigita 5 per il supernetting\ndigita 0 per uscire\n");
	    	scanf("%d",&scelta);
        switch(scelta)
        {
        case 1:
            classi(ip,ipb);
        break;
        case 2:
            verifica();
        break;
        case 3:
            calcolatore(ip,ipb,nbitr,sm,rbin,nib);
        break;
        case 4:
            verifica2(ip,ipb,nbitr,sm,rbin,nib);
		break;
		case 5:
			supernetting(ip,ipb,nbitr,sm,rbin,nib);
        break;
	    }
    }while(scelta!=0);
}

int classi(int ip[],int ipb[])
{
   int j,i,classe,cont,slash;
    conversione(ip,ipb);			//chiamata alla funzione dell'input
    classe=1;
		j=0;
    for(cont=1;cont==1;j++)             //controllo della classe dell'indirizzo tramite il numero di uno ad inizio indirizzo
    {
        if(ipb[j]==0)
        {
            cont=0;
        }
        else
        {
            classe++;
        }
    }
    switch(classe)                      //switch per stampa della classe e controllo per vedere se l'indirizzo e' pubblico o privato
    {
    case 1:
            printf("\nl'indirizzo e' di classe A");
            if(ip[0]==10)
            {
                printf("\nl'indirizzo e' privato");
                slash=8;
            }
            else
            {
                printf("\nl'indirizzo e' pubblico");
                slash=8;
            }
    break;
    case 2:
            printf("\nl'indirizzo e' di classe B");
            if(ip[0]==172 && ip[1]>=16 && ip[1]<=31)
            {
                printf("\nl'indirizzo e' privato");
                slash=16;
            }
            else
            {
                printf("\nl'indirizzo e' pubblico");
                slash=16;
            }
    break;
    case 3:
            printf("\nl'indirizzo e' di classe C");
            if(ip[0]==192 && ip[1]==168)
            {
                printf("\nl'indirizzo e' privato");
                slash=24;
            }
            else
            {
                printf("\nl'indirizzo e' pubblico");
                slash=24;
            }
    break;
    case 4:
            printf("\nl'indirizzo e' di classe D");
    break;
    case 5:
            printf("\nl'indirizzo e' di classe E");
    break;
    }
    return slash;
}

void verifica()
{
     int n1[4], n2[4], sm[4],i,cont=0;
    //primo ip
    for(i=0;i<4;i++)
    {
				do
				{
      			printf("\ninserisci il %d numero del primo indirizzo:",i+1);
      			scanf("%d",&n1[i]);
				}while(n1[i]>255||n1[i]<0);
    }
    //secondo ip
    for(i=0;i<4;i++)
    {
				do
				{
        		printf("\ninserisci il %d numero del secondo indirizzo:",i+1);
        		scanf("%d",&n2[i]);
				}while(n2[i]>255||n2[i]<0);
    }
    //subnetmask
    for(i=0;i<4;i++)
    {
				do
				{
        		printf("\ninserisci il %d numero della subnetmask:",i+1);
        		scanf("%d",&sm[i]);
				}while(sm[i]>255||sm[i]<0);
    }
    for(i=0;i<4;i++)
    {
        if((n1[i]&sm[i])==(n2[i]&sm[i]))   //and tra ip e subnetmask2; se sono tutti e quattro i numeri uguali i due indirizzi appartengono alla stessa sottorete
        {
            cont++;
        }
    }
    if(cont==4)
    {
        printf("\nsi appartengono alla stessa rete\n");
    }else
        {
            printf("\nno, non appartengono alla stessa rete\n");
        }
}

void conversione(int ip[],int ipb[])
{
    int i, j, num;
    for(i=0;i<4;i++)
    {                           //input ip
        do
        {
            printf("Inserisci numero %d dell'indirizzo IP:\t",i+1);           //input dell'indirizzo e relativa conversione in binario
            scanf("%d",&ip[i]);
        }while(ip[i]>255||ip[i]<0);
    }
	for(i=0;i<4;i++)
    {                           //conversione ip in binario
		num=ip[i];
		for(j=7+8*i;j>8*i-1;j--)
        {
		    if(num%2==0)
		        ipb[j]=0;
		    else
		        ipb[j]=1;
		    num=num/2;
		}
	}
}

void calcolatore(int ip[],int ipb[],int nbitr,int sm,int rbin[],int nib[])				//funzione per il calcolo delle sottoreti a maschera fissa
{
    int nsub,cont,stamp;
    int i,j=0,dec,host;
    int sum[j];
    sm=classi(ip,ipb);              //uso la funzione classi per determinare con quale classe di indirizzo lavorare
    switch(sm)                      //switch per le diverse classi
    {
    case 8:                         //l'unica differenza tra i diversi case è il controllo per le sottoreti inseribili
            nbitr=0;
            do
            {
                printf("\ninserisci il numero di sottoreti da calcolare (4194304/1)\n");
                scanf("%d",&nsub);
            }while(nsub>4194304||nsub<=0);                      //controllo per le sottoreti
            while(nsub>pow(2,nbitr))
            {
                nbitr++;
                j++;
            }
            do
            {
                printf("\npremere 0 per la stampa in binario o 1 per la stampa in decimale\n");
                scanf("%d",&stamp);
            }while(stamp>1||stamp<0);                   //decisione se stampare in binario o in decimale
            cont=j;
            nbitr=nbitr+sm;
            printf("subnet mask(notazione CIDR):%d\n",nbitr);
            host=pow(2,32-nbitr);
            printf("numero host per sottorete:%d\n",host);          //host disponibili per sottorete
            for(i=1;i<=j;i++)
            {
                rbin[i]=ipb[sm+1+i];
            }
            for(i=0; i<=j; i++)
            {
                sum[i]=0;
            }
            subnet(nbitr);
			printf("\n ");
			if(stamp ==1)
			{
			    for(i=0;i<112;i++)
    		    {
			        printf("-");
			    }
				printf("\n");
				printf("|  n subnet |\t\tnet id\t\t|\t\tbroadcast \t|\t\tgateway\t\t|\t\t\t\trange \t\t\t\t\t|\n");
				for(i=0;i<112;i++)
    			{
					printf("-");
				}
				printf("\n");	
			}
			if(stamp==0)
			{
				for(cont=0;cont<nsub;cont++)																	//blocco per il calcolo effettivo delle subnet in binario
         		{
               		printf("\nnumero subnet:%d\n",cont+1);
               		netid(ip,ipb,nbitr,nib,stamp);
               		broad(ip,ipb,nbitr,nib,stamp);
               		gw(ip,ipb,nbitr,nib,stamp);
               		range(ip,ipb,nbitr,nib,stamp);
               		addBinary(rbin,j,sm,nbitr,ipb,sum);
					printf("\n");
				}
			}else
				{
                    for(cont=0;cont<nsub;cont++)																	//blocco per il calcolo effettivo delle subnet i decimale
                    {
                        printf("|");
                        printf("\t  %d  \t",cont+1);
                        printf("|");
                        netid(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        broad(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        gw(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        range(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        addBinary(rbin,j,sm,nbitr,ipb,sum);
                        for(i=0;i<112;i++)
                        {
                            printf("-");
                        }
                        printf("\n");
                    }
	    		}
    break;
    case 16:
            nbitr=0;
            do
            {
                printf("\ninserisci il numero di sottoreti da calcolare (16384/1)\n");
                scanf("%d",&nsub);
            }while(nsub>16384||nsub<=0);
            while(nsub>pow(2,nbitr))
            {
                nbitr++;
                j++;
            }
            do
            {
                printf("\npremere 0 per la stampa in binario o 1 per la stampa in decimale\n");
                scanf("%d",&stamp);
            }while(stamp>1||stamp<0);
            cont=j;
            nbitr=nbitr+sm;
            printf("subnet mask(notazione CIDR):%d\n",nbitr);
            host=pow(2,32-nbitr);
            printf("numero host per sottorete:%d\n",host);
            for(i=1;i<=j;i++)
            {
                rbin[i]=ipb[sm+1+i];
            }
            for(i=0; i<=j; i++)
            {
                sum[i]=0;
            }
            subnet(nbitr);
			printf("\n ");
			if(stamp ==1)
			{
			    for(i=0;i<112;i++)
    		    {
			        printf("-");
			    }
				printf("\n");
				printf("|  n subnet |\t\tnet id\t\t|\t\tbroadcast \t|\t\tgateway\t\t|\t\t\t\trange \t\t\t\t\t|\n");
				for(i=0;i<112;i++)
    			{
					printf("-");
				}
				printf("\n");	
			}
			if(stamp==0)
			{
				for(cont=0;cont<nsub;cont++)																	//blocco per il calcolo effettivo delle subnet
         		{
               		printf("\nnumero subnet:%d\n",cont+1);
               		netid(ip,ipb,nbitr,nib,stamp);
               		broad(ip,ipb,nbitr,nib,stamp);
               		gw(ip,ipb,nbitr,nib,stamp);
               		range(ip,ipb,nbitr,nib,stamp);
               		addBinary(rbin,j,sm,nbitr,ipb,sum);
					printf("\n");
				}
			}else
				{
                    for(cont=0;cont<nsub;cont++)																	//blocco per il calcolo effettivo delle subnet
                    {
                        printf("|");
                        printf("\t  %d  \t",cont+1);
                        printf("|");
                        netid(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        broad(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        gw(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        range(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        addBinary(rbin,j,sm,nbitr,ipb,sum);
                        for(i=0;i<112;i++)
                        {
                            printf("-");
                        }
                        printf("\n");
                    }
	    		}
    break;
    case 24:
            nbitr=0;
            do
            {
                printf("\ninserisci il numero di sottoreti da calcolare (64/1)\n");
                scanf("%d",&nsub);
            }while(nsub>64||nsub<=0);
            while(nsub>pow(2,nbitr))
            {
                nbitr++;
                j++;
            }
            do
            {
                printf("\npremere 0 per la stampa in binario o 1 per la stampa in decimale\n");
                scanf("%d",&stamp);
            }while(stamp>1||stamp<0);
            cont=j;
            nbitr=nbitr+sm;
            printf("subnet mask(notazione CIDR):%d\n",nbitr);
            host=pow(2,32-nbitr);
            printf("numero host per sottorete:%d\n",host);
            for(i=1;i<=j;i++)
            {
                rbin[i]=ipb[sm+1+i];
            }
            for(i=0; i<=j; i++)
            {
                sum[i]=0;
            }
            subnet(nbitr);
			printf("\n ");
			if(stamp ==1)
			{
			    for(i=0;i<112;i++)
    		    {
			        printf("-");
			    }
				printf("\n");
				printf("|  n subnet |\t\tnet id\t\t|\t\tbroadcast \t|\t\tgateway\t\t|\t\t\t\trange \t\t\t\t\t|\n");
				for(i=0;i<112;i++)
    			{
					printf("-");
				}
				printf("\n");	
			}
			if(stamp==0)
			{
				for(cont=0;cont<nsub;cont++)																	//blocco per il calcolo effettivo delle subnet
         		{
               		printf("\nnumero subnet:%d\n",cont+1);
               		netid(ip,ipb,nbitr,nib,stamp);
               		broad(ip,ipb,nbitr,nib,stamp);
               		gw(ip,ipb,nbitr,nib,stamp);
               		range(ip,ipb,nbitr,nib,stamp);
               		addBinary(rbin,j,sm,nbitr,ipb,sum);
					printf("\n");
				}
			}else
				{
                    for(cont=0;cont<nsub;cont++)																	//blocco per il calcolo effettivo delle subnet
                    {
                        printf("|");
                        printf("\t  %d  \t",cont+1);
                        printf("|");
                        netid(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        broad(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        gw(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        range(ip,ipb,nbitr,nib,stamp);
                        printf("|");
                        addBinary(rbin,j,sm,nbitr,ipb,sum);
                        for(i=0;i<112;i++)
                        {
                            printf("-");
                        }
                        printf("\n");
                    }
	    		}
    break;
    }
}

void addBinary(int rbin[],int j,int sm,int nbitr,int ipb[],int sum[])      //funzione per l'incremento dei bit dei bit della rete e quindi l'avanzare del numero della subnet
{
    int i, c = 0;
    int a[j];
    for(i=0;i<=j;i++)
    {
        if(i!=j)
        {
            a[i]=0;
        }else
            {
                a[i]=1;
            }
    }

    for(i = j; i > 0 ; i--)             //tramite gli and bit  bit sommo 1 in binario in modo di ottenere la subnet successiva
    {
       sum[i] = ((a[i] ^ rbin[i]) ^ c);
       c = ((a[i] & rbin[i]) | (a[i] & c)) | (rbin[i] & c);
    }
    sum[i] = c;
    printf("\n");
    int z=1;
    for(i=sm; i<nbitr; i++)
    {
       ipb[i]=sum[z];
       rbin[z]=ipb[i];
       z++;
    }
}

void addBinary2(int rbin[],int j,int sm,int nbitr,int ipb[],int sum[])      //funzione per l'incremento dei bit dei bit della rete e quindi l'avanzare del numero della subnet
{
    int i, c = 0;
    int a[nbitr];
    for(i=0;i<=nbitr;i++)
    {
        if(i!=nbitr)
        {
            a[i]=0;
        }else
            {
                a[i]=1;
            }
    }

    for(i = nbitr; i > 0 ; i--)             //tramite gli and bit a bit sommo 1 in binario in modo di ottenere la subnet successiva
    {
       sum[i] = ((a[i] ^ rbin[i]) ^ c);			//^=xor
       c = ((a[i] && rbin[i]) || (a[i] && c)) || (rbin[i] && c);
    }
    sum[i] = c;
    printf("\n");
    int z=1;
    for(i=nbitr-1; i<=sm; i++)//erroreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
    {
       ipb[i]=sum[z];
       rbin[z]=ipb[i];
       z++;
    }
}

void decimale(int nib[])                //funzione per la conversione da binario a decimale
{
	int dec[4],i=0,j,app=0;
	int  somma, potenz, cont;
    i = 0;
    for (j = 0; j < 4; j++)
    {
        cont = 7;
        somma = 0;
        do
        {
            potenz = pow(2, cont);
            app = nib[i];
            app = app * potenz;
            somma = somma + app;
            cont--;
            i++;
        } while (cont >= 0);
        dec[j]=somma;
    }
		printf("\t");
    for (j = 0; j < 4; j++)
    {
        printf("%0.3d",dec[j]);
        if(j!=3)
        {
            printf(".");
        }
    }
    printf("\t");
}

void subnet(int nbitr)															//funzione per la stampa della subnetmask
{
    int nib[31],i,j=0;
    for(i=0;i<32;i++)
    {
        if(i>=nbitr)
        {
            nib[i]=0;
        }else
            {
                nib[i]=1;
            }
    }
		printf("subnet mask:\n");
 //stampa binario
    for(i=0;i<32;i++)
    {
        printf("%d",nib[i]);
		if(i==7 || i==15 || i==23)
		{
			printf(".");
		}
    }
    printf(" / ");
	decimale(nib);
}

void netid(int ip[],int ipb[],int nbitr,int nib[],int stamp)				//funzione per il calcolo del netid
{
    int i,j=0;
    for(i=0;i<32;i++)
    {
        if(i>=nbitr)
        {
            nib[i]=0;
        }else
            {
                nib[i]=ipb[i];
            }
    }
  //stampa binario
  if(stamp==0)
  {
		printf("net id:\t");
    for(i=0;i<32;i++)
    {
        printf("%d",nib[i]);
		if(i==7 || i==15 || i==23)
		{
			printf(".");
		}
    }
		printf("\n");
 }else
    {
        decimale(nib);
    }
}

void broad(int ip[],int ipb[],int nbitr,int nib[],int stamp)				//funzione per il calcolo del broadcast
{
    int i,j=0;
    for(i=0;i<32;i++)
    {
        if(i>=nbitr)
        {
            nib[i]=1;
        }else
            {
                nib[i]=ipb[i];
            }
    }
		if(stamp ==0)
		{
		//stampa binario
		printf("broadcast:\t");
    for(i=0;i<32;i++)
    {
        printf("%d",nib[i]);
		if(i==7 || i==15 || i==23)
		{
			printf(".");
		}
    }
		printf("\n");
		}else
    {
	    decimale(nib);
    }
}

void gw(int ip[],int ipb[],int nbitr,int nib[],int stamp)				//funzione per il calcolo del gateway
{
    int i,j=0;
    for(i=0;i<32;i++)
    {
        if(i>=nbitr)
        {
            if(i==31)
            {
                nib[i]=1;
            }else
                {
                    nib[i]=0;
                }
        }else
            {
                nib[i]=ipb[i];
            }
    }
    if(stamp ==0)
    {
    //stampa binario
		printf("gateway:\t");
        for(i=0;i<32;i++)
        {
            printf("%d",nib[i]);
            if(i==7 || i==15 || i==23)
            {
                printf(".");
            }
        }
				printf("\n");
    }else
    {
	    decimale(nib);
    }
}

void range(int ip[],int ipb[],int nbitr,int nib[],int stamp)				//funzione per il calcolo del range degli host
{
    //primo host
    int i,j=0;
    for(i=0;i<32;i++)
    {
        if(i>=nbitr)
        {
            if(i==30)
            {
                nib[i]=1;
            }else
                {
                    nib[i]=0;
                }
        }else
            {
                nib[i]=ipb[i];
            }
    }
    if(stamp ==0)
    {
		//stampa binario
		printf("range:\nprimo host:\t");
		for(i=0;i<32;i++)
		{
			printf("%d",nib[i]);
			if(i==7 || i==15 || i==23)
			{
				printf(".");
			}
		}
	    printf("\n");
    }else
    {
	    decimale(nib);
    }
    //ultimo host
    for(i=0;i<32;i++)
    {
        if(i>=nbitr)
        {
            if(i==31)
            {
                nib[i]=0;
            }else
                {
                    nib[i]=1;
                }
        }else
            {
                nib[i]=ipb[i];
            }
    }
    if(stamp ==0)
    {
		//stampa binario
		printf("ultimo host:\t");
		for(i=0;i<32;i++)
		{
			printf("%d",nib[i]);
		    if(i==7 || i==15 || i==23)
		    {
			    printf(".");
		    }
		}
		printf("\n");
    }else
    {
	    decimale(nib);
    }
}

void verifica2(int ip[],int ipb[],int nbitr,int sm,int rbin[],int nib[])							//funzione per il calcolo delle subnet a maschera variabile
{
    int nsub,cont,host[MAX],nbith=0;
    int i,j=0,dec,nhost,app,tot=0,stamp;
    int sum[j];
    sm=classi(ip,ipb);
    switch(sm)
    {
    case 8:                                                             //tra i vari case cambia solo il controllo per le subnet inseribili e per gli host massimi inseribili
            nbitr=0;
            do
            {
                printf("\ninserisci il numero di sottoreti da calcolare (4194304/1)\n");
                scanf("%d",&nsub);
            }while(nsub>4194304||nsub<=0);
            //input host
            for(i=0;i<nsub;i++)
            {
                printf("\ninserisci il numero di host per la sottorete numero %d\n",i+1);
                scanf("%d",&host[i]);
                host[i]=host[i]+3;
            }
            //controllo possibilità di fare le subnet richieste
            for(cont=0;cont<nsub;cont++)
            {
				nbith=0;
                while(host[cont]>pow(2,nbith))
                    {
                        nbith++;
                    }
                nbitr=32-nbith;
                nhost=pow(2,32-nbitr);
                tot=tot+nhost;
            }
            if(tot>4194304)
            {
                printf("impossibile soddisfare tale richiesta\n");
                break;
            }
            do
            {
                printf("\npremere 0 per la stampa in binario o 1 per la stampa in decimale\n");
                scanf("%d",&stamp);
            }while(stamp>1||stamp<0);
            //ordinamento host
            for (i = 0; i < nsub; ++i)
            {
                for (j = i + 1; j < nsub; ++j)
                {
                    if (host[i] < host[j])
                    {
                        app = host[i];
                        host[i] = host[j];
                        host[j] = app;
                    }
                }
            }
            for(cont=0;cont<nsub;cont++)
            {
            	nbith=0;
            	while(host[cont]>pow(2,nbith))
	                {
	                    nbith++;
	                }
	            nbitr=32-nbith;
                j=nbitr-sm;
				nhost=pow(2,32-nbitr);
                for(i=1;i<=j;i++)
                {
                    rbin[i]=ipb[sm+1+i];
                }
                for(i=0; i<=j; i++)
                {
                    sum[i]=0;
                }
                subnet(nbitr);
				printf("\n");
	                if(stamp==0)
                    {                                             //blocco per il calcolo per la subnet
                        printf("\nnumero host per sottorete:%d\n",nhost);
                        printf("subnet mask(notazione CIDR):%d\n",nbitr);
                        printf("\nnumero subnet:%d\n",cont+1);
                        netid(ip,ipb,nbitr,nib,stamp);
                        broad(ip,ipb,nbitr,nib,stamp);
                        gw(ip,ipb,nbitr,nib,stamp);
                        range(ip,ipb,nbitr,nib,stamp);
                        addBinary(rbin,j,sm,nbitr,ipb,sum);
                    }else
                        {                                            //blocco per il calcolo per la subnet
                                printf("\nnumero host per sottorete:%d\n",nhost);
                                printf("subnet mask(notazione CIDR):%d\n",nbitr);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                                printf("|  n subnet |\t\tnet id\t\t|\t\tbroadcast \t|\t\tgateway\t\t|\t\t\t\trange \t\t\t\t\t|\n");
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");	
                                printf("|");
                                printf("\t  %d  \t",cont+1);
                                printf("|");
                                netid(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                broad(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                gw(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                range(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                addBinary(rbin,j,sm,nbitr,ipb,sum);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                        }
            }
    break;
    case 16:
            nbitr=0;
            do
            {
                printf("\ninserisci il numero di sottoreti da calcolare (16384/1)\n");
                scanf("%d",&nsub);
            }while(nsub>16384||nsub<=0);
            //input host
            for(i=0;i<nsub;i++)
            {
                printf("\ninserisci il numero di host per la sottorete numero %d\n",i+1);
                scanf("%d",&host[i]);
                host[i]=host[i]+3;
            }
            //controllo possibilità di fare le subnet richieste
            for(cont=0;cont<nsub;cont++)
            {
							nbith=0;
                while(host[cont]>pow(2,nbith))
                    {
                        nbith++;
                    }
                nbitr=32-nbith;
                nhost=pow(2,32-nbitr);
                tot=tot+nhost;
            }
            if(tot>65536)
            {
                printf("impossibile soddisfare tale richiesta\n");
                break;
            }
            do
            {
                printf("\npremere 0 per la stampa in binario o 1 per la stampa in decimale\n");
                scanf("%d",&stamp);
            }while(stamp>1||stamp<0);
            //ordinamento host
            for (i = 0; i < nsub; ++i)
            {
                for (j = i + 1; j < nsub; ++j)
                {
                    if (host[i] < host[j])
                    {
                        app = host[i];
                        host[i] = host[j];
                        host[j] = app;
                    }
                }
            }
            for(cont=0;cont<nsub;cont++)
            {
            	nbith=0;
            	while(host[cont]>pow(2,nbith))
	                {
	                    nbith++;
	                }
	                nbitr=32-nbith;
                j=nbitr-sm;
				nhost=pow(2,32-nbitr);
                for(i=1;i<=j;i++)
                {
                    rbin[i]=ipb[sm+1+i];
                }
                for(i=0; i<=j; i++)
                {
                    sum[i]=0;
                }
                subnet(nbitr);
	                if(stamp==0)
                    { 
                        printf("\nnumero host per sottorete:%d\n",nhost);
                        printf("subnet mask(notazione CIDR):%d\n",nbitr);
                        printf("\nnumero subnet:%d\n",cont+1);
                        netid(ip,ipb,nbitr,nib,stamp);
                        broad(ip,ipb,nbitr,nib,stamp);
                        gw(ip,ipb,nbitr,nib,stamp);
                        range(ip,ipb,nbitr,nib,stamp);
                        addBinary(rbin,j,sm,nbitr,ipb,sum);
                    }else
                        {
                                printf("\nnumero host per sottorete:%d\n",nhost);
                                printf("subnet mask(notazione CIDR):%d\n",nbitr);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                                printf("|  n subnet |\t\tnet id\t\t|\t\tbroadcast \t|\t\tgateway\t\t|\t\t\t\trange \t\t\t\t\t|\n");
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");	
                                printf("|");
                                printf("\t  %d  \t",cont+1);
                                printf("|");
                                netid(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                broad(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                gw(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                range(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                addBinary(rbin,j,sm,nbitr,ipb,sum);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                        }
            }
    break;
    case 24:
            nbitr=0;
            do
            { //input numero subnet
                printf("\ninserisci il numero di sottoreti da calcolare (64/1)\n");
                scanf("%d",&nsub);
            }while(nsub>64||nsub<=0);
            //input host
            for(i=0;i<nsub;i++)
            {
                printf("\ninserisci il numero di host per la sottorete numero %d\n",i+1);
                scanf("%d",&host[i]);
                host[i]=host[i]+3;
            }
            //controllo possibilità di fare le subnet richieste
            for(cont=0;cont<nsub;cont++)
            {
							nbith=0;
                while(host[cont]>pow(2,nbith))
                    {
                        nbith++;
                    }
                nbitr=32-nbith;
                nhost=pow(2,32-nbitr);
                tot=tot+nhost;
            }
            if(tot>256)
            {
                printf("impossibile soddisfare tale richiesta\n");
                break;
            }
            do
            {
                printf("\npremere 0 per la stampa in binario o 1 per la stampa in decimale\n");
                scanf("%d",&stamp);
            }while(stamp>1||stamp<0);
            //ordinamento host
            for (i = 0; i < nsub; ++i)
            {
                for (j = i + 1; j < nsub; ++j)
                {
                    if (host[i] < host[j])
                    {
                        app = host[i];
                        host[i] = host[j];
                        host[j] = app;
                    }
                }
            }
            for(cont=0;cont<nsub;cont++)
            {
            	nbith=0;
            	while(host[cont]>pow(2,nbith))
	                {
	                    nbith++;
	                }
	            nbitr=32-nbith;
            	j=nbitr-sm;
				nhost=pow(2,32-nbitr);
              for(i=1;i<=j;i++)
              {
                  rbin[i]=ipb[sm+1+i];
              }
              for(i=0; i<=j; i++)
              {
                  sum[i]=0;
              }
              subnet(nbitr);
                  if(stamp==0)
                    { 
                        printf("\nnumero host per sottorete:%d\n",nhost);
                        printf("subnet mask(notazione CIDR):%d\n",nbitr);
                        printf("\nnumero subnet:%d\n",cont+1);
                        netid(ip,ipb,nbitr,nib,stamp);
                        broad(ip,ipb,nbitr,nib,stamp);
                        gw(ip,ipb,nbitr,nib,stamp);
                        range(ip,ipb,nbitr,nib,stamp);
                        addBinary(rbin,j,sm,nbitr,ipb,sum);
                    }else
                        {
                                printf("\nnumero host per sottorete:%d\n",nhost);
                                printf("subnet mask(notazione CIDR):%d\n",nbitr);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                                printf("|  n subnet |\t\tnet id\t\t|\t\tbroadcast \t|\t\tgateway\t\t|\t\t\t\trange \t\t\t\t\t|\n");
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");	
                                printf("|");
                                printf("\t  %d  \t",cont+1);
                                printf("|");
                                netid(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                broad(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                gw(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                range(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                addBinary(rbin,j,sm,nbitr,ipb,sum);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                        }
            }
    break;
    }
}

void supernetting(int ip[],int ipb[],int nbitr,int sm,int rbin[],int nib[])							//funzione per il calcolo delle subnet a maschera variabile
{
    int nsub,cont,host[MAX],nbith=0;
    int i,j=0,dec,nhost,app,tot=0,stamp;
    int sum[j];
    sm=classi(ip,ipb);
    switch(sm)
    {
    case 8:
			printf("errore");
    break;
    case 16:
			printf("errore");
    break;
    case 24:
            nbitr=0;
            do
            { //input numero subnet
                printf("\ninserisci il numero di sottoreti da calcolare (64/1)\n");
                scanf("%d",&nsub);
            }while(nsub>64||nsub<=0);
            //input host
            for(i=0;i<nsub;i++)
            {
                printf("\ninserisci il numero di host per la sottorete numero %d\n",i+1);
                scanf("%d",&host[i]);
                host[i]=host[i]+3;
            }
            do
            {
                printf("\npremere 0 per la stampa in binario o 1 per la stampa in decimale\n");
                scanf("%d",&stamp);
            }while(stamp>1||stamp<0);
            //ordinamento host
            for (i = 0; i < nsub; ++i)
            {
                for (j = i + 1; j < nsub; ++j)
                {
                    if (host[i] < host[j])
                    {
                        app = host[i];
                        host[i] = host[j];
                        host[j] = app;
                    }
                }
            }
            for(cont=0;cont<nsub;cont++)
            {
            	nbith=0;
            	while(host[cont]>pow(2,nbith))
	                {
	                    nbith++;
	                }
	            nbitr=32-nbith;
            	j=nbitr-sm;
				if(j<0)
				{
					j=j*-1;
					printf("%d",j);
				}
				nhost=pow(2,32-nbitr);
              for(i=0;i<=nbitr;i++)
              {
                  rbin[i]=ipb[i];		
              }
              for(i=0; i<=nbitr; i++)
              {
                  sum[i]=0;
              }
              subnet(nbitr);
                  if(stamp==0)
                    { 
                        printf("\nnumero host per sottorete:%d\n",nhost);
                        printf("subnet mask(notazione CIDR):%d\n",nbitr);
                        printf("\nnumero subnet:%d\n",cont+1);
                        netid(ip,ipb,nbitr,nib,stamp);
                        broad(ip,ipb,nbitr,nib,stamp);
                        gw(ip,ipb,nbitr,nib,stamp);
                        range(ip,ipb,nbitr,nib,stamp);
                        addBinary2(rbin,j,sm,nbitr,ipb,sum);
                    }else
                        {
                                printf("\nnumero host per sottorete:%d\n",nhost);
                                printf("subnet mask(notazione CIDR):%d\n",nbitr);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                                printf("|  n subnet |\t\tnet id\t\t|\t\tbroadcast \t|\t\tgateway\t\t|\t\t\t\trange \t\t\t\t\t|\n");
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");	
                                printf("|");
                                printf("\t  %d  \t",cont+1);
                                printf("|");
                                netid(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                broad(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                gw(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                range(ip,ipb,nbitr,nib,stamp);
                                printf("|");
                                addBinary2(rbin,j,sm,nbitr,ipb,sum);
                                for(i=0;i<112;i++)
                                {
                                    printf("-");
                                }
                                printf("\n");
                        }
            }
    break;
    }
}
