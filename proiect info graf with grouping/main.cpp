
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <Shellapi.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <dirent.h>
using namespace std;


struct {char numefisiere[100];}v[200000];
// sa unesc structurile intre ele sa nu fac cu limitagrup ,sa fac ca la structu de sus
struct {int t[65500];}grup[4];

int limitagrup=65500;
char hmm[203],oh[203];
char pathm[500]="D:",pathafis[500];
int r[100003], n=1, np=2, nt=0, ischimb, ppathmb, i_fis_adaug;
bool okk, allfiles=1, padresa=1, totfis=0, e_fis=0;



void listFile(){
    int i=0, it=0;
    v[0].numefisiere[0]='D';
    v[0].numefisiere[1]=':';
    v[0].numefisiere[2]='/';
    char path[500]="D:/";
	DIR *dir;
    struct dirent *ent;
    do{
    dir = opendir (path);
    //cout<<path<<'\n';
  /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL){
        strcpy(v[n++].numefisiere, ent->d_name);
        //cout<<n-1<<v[n-1].numefisiere<<'\n';
        if (v[n-1].numefisiere[0]=='.' && (v[n-1].numefisiere[1]=='.' || v[n-1].numefisiere[1]==NULL))
            --n;
        else {
            grup[++it/limitagrup].t[it%limitagrup]=i;
            //r[n]=r[t[n]]+1; daca il folosesc sa il fac ca pe t
            }
    }
    //inchid ce folosesc dupa ce folosesc si nu mai imi trebuie...
    closedir(dir);
    ++i;
    strcpy(path,"D:");
    int adr[20], nadr=0, e=1;
    adr[nadr]=i;
    while (grup[adr[nadr]/limitagrup].t[adr[nadr]%limitagrup])
        adr[++nadr]=grup[adr[nadr-1]/limitagrup].t[adr[nadr-1]%limitagrup];
    while (nadr>=0){
            path[++e]='/';
        for (int z=0; v[adr[nadr]].numefisiere[z]; ++z){
            path[++e]=v[adr[nadr]].numefisiere[z];
        }
        --nadr;
    }
    for (int z=e+1; path[z]; ++z)
        path[z]=NULL;
    //cout<<path<<'\n';
    //closedir (dir);
    //if ((dir = opendir (path)) == NULL)
    // could not open directory /
    //cout<<"NU";
    }while (n<100000);
    i_fis_adaug=n-1;
    closedir(dir);
}

bool e_adr(char hmm[]){
    bool ok=0;
    for (int i=0; hmm[i]; ++i)
        if (hmm[i]==92 || hmm[i]=='/'){
        ok=1;
        break;
        }
    return ok;
}

void mutare_rand(char name[]){



}

void mutare(char oldname[], char newname[]){
    //system("CLS");
    bool ok=0;
    char wtf[3]="\/";
    for (int i=0; newname[i]; ++i)
        if (newname[i]==wtf[0] || newname[i]==wtf[1]){
            ok=1;
            break;
        }
    int res=rename(oldname, newname);
    if (res==0){
        puts("File successfully moved to ");
        cout<<newname;
        //sa ii schimb t-ul
    }

}

void redenumire(char oldname[], char newname[]){
    //system("CLS");
    int res=rename(oldname, newname);
    if (res==0){
        int i=0;
        puts ( "File successfully renamed" );
        while (newname[ppathmb]){
            v[ischimb].numefisiere[i]=newname[ppathmb];
            ++i;
            ++ppathmb;
        }
        while (v[ischimb].numefisiere[i]){
            v[ischimb].numefisiere[i]=NULL;
            ++i;
        }
    }else
        perror( "Error renaming file" );
}

void findpath(char filename[]){
    char nume[90];
    if (e_adr(filename)==1){
        allfiles=0;
        padresa=0;
        int a=0,b=0;
        while (filename[a]) ++a;
        while (filename[a]!=92 && filename[a]!='/')
            --a;
        ++a;
        while (filename[a]){
            nume[b++]=filename[a++];
        }
        nume[b]=NULL;
    }
    else strcpy(nume,filename);
    int i=1,adr[20],ca=0;
    for (int i=2; pathm[i]; ++i)
        pathm[i]=NULL;
    np=1;
    okk=0;
    while (i<n){
        if (strcmp(nume, v[i].numefisiere)==0){
            ischimb=i;
            int k=i;
            while (grup[k/limitagrup].t[k%limitagrup]){
                adr[ca++]=k;
                k=grup[k/limitagrup].t[k%limitagrup];
            }
            adr[ca]=k;
            for (int j=ca; j>=0; --j){
                pathm[++np]='/';
                for (int o=0; v[adr[j]].numefisiere[o]; ++o)
                    pathm[++np]=v[adr[j]].numefisiere[o];
            }
            okk=1;
            if (allfiles==1)
                break;
            else {
                if (padresa==0){
                    if (strcmp(pathm, filename)==0)
                        break;
                }else cout<<pathm<<'\n';
                //daca userul introduce adresa
                for (int i=2; pathm[i]; ++i)
                    pathm[i]=NULL;
                ca=0;
                np=1;
            }
        }
        ++i;
    }
    if (!okk)
        cout<<"Nu Exista Fisier/Document cu numele acesta";
    allfiles=1;
    padresa=1;
}

void pathi(int i){
    np=1;
    for (int i=2; pathm[i]; ++i)
        pathm[i]=NULL;
    int k=i,adr[20],ca=0;
    while (grup[k/limitagrup].t[k%limitagrup]){
        adr[ca++]=k;
        k=grup[k/limitagrup].t[k%limitagrup];
    }
    adr[ca]=k;
    for (int j=ca; j>=0; --j){
        pathm[++np]='/';
        for (int o=0; v[adr[j]].numefisiere[o]; ++o)
            pathm[++np]=v[adr[j]].numefisiere[o];
    }
}

void afis(){
    if (e_fis==0){
        cout<<"Fisierul in care vreti sa vedeti folderele:";
        cin>>hmm;
        findpath(hmm);
        strcpy(pathafis, pathm);
        if (okk)
            e_fis=1;
        else {cout<<" Reincercati"<<'\n';
        afis();
        }
    }
        ofstream fout(pathafis);
        for (int j=0; j<n; ++j){
            if (grup[j/limitagrup].t[j%limitagrup]!=-1){
                if (grup[j/limitagrup].t[j%limitagrup]!=grup[(j-1)/limitagrup].t[(j-1)%limitagrup]){
                    pathi(grup[j/limitagrup].t[j%limitagrup]);
                    fout<<'\n'<<pathm<<'\n';
                }
                fout<<v[j].numefisiere<<'\n';
            }
        }
        fout.close();
    ShellExecute(NULL, "open", pathafis, NULL, NULL, SW_SHOWDEFAULT);
}

//cu functia asta sa fac si tot ce este in fisier cu subfoldere
//transmit si un char cu path care se adauga recursiv
void delete_fisier(int i , int is){
    while (grup[i/limitagrup].t[i%limitagrup]!=is && i<=n) ++i;
    if (i>n){
        //folderul ce trebuie sters e gol direct
        if (RemoveDirectoryA(pathm) == 0)
            DeleteFileA(pathm);
        grup[is/limitagrup].t[is%limitagrup]=-1;
    }
    if (i<=n){
        while (grup[i/limitagrup].t[i%limitagrup]==is){
            pathi(i);
            if (RemoveDirectoryA(pathm) == 0 && DeleteFileA(pathm)==0){
                //folderul nu e gol
                delete_fisier(i+1, i);
            }
            pathi(i);
            grup[i/limitagrup].t[i%limitagrup]=-1;
            cout<<pathm<<'\n';
            if (RemoveDirectoryA(pathm) == 0)
                DeleteFileA(pathm);
            ++i;
        }
    }
}

//void add(char fisier[]){}
//void deschidere_fisier(char fisier[]){}

void ce_este_in_fisier(char fisier[]){
    findpath(fisier);
    int i=ischimb, ii=ischimb;
    while (grup[i/limitagrup].t[i%limitagrup]!=ischimb && i<=n) ++i;
    if (i>n && totfis==0)
        cout<<fisier<<" este un document (nu poate avea subfoldere) sau este un fisier gol.";
    if (i<=n && okk==1){
        ////////////////////////////de ce imi face ca pathm este D:
        if(totfis==0){
            if (e_adr(hmm)==1)
                cout<<hmm<<'\n';
            else
                cout<<pathm<<'\n';
        }
        while (grup[i/limitagrup].t[i%limitagrup]==ii){
            if (totfis==0)
                cout<<v[i].numefisiere<<'\n';
            else {
                int j=0;
                pathm[++np]='/';
                for (int o=np+1; v[i].numefisiere[j]; ++j)
                    pathm[o+j]=v[i].numefisiere[j];
                pathm[j+np+1]=NULL;
                cout<<pathm<<'\n';
                char cop[200];
                strcpy(cop,pathm);
                ////copie la pathm si sa fac la strcmp de copie si pathm si atunci sa dau break
                ce_este_in_fisier(cop);
            }
            ++i;
        }
    }
    while (pathm[np]!='/') pathm[np--]=NULL;
        pathm[np--]=NULL;
}

int main(){
    listFile();
    int caz;
    cout<<"Ce vreti sa faceti?"<<'\n'<<'\n'<<"1. afisarea folderelor"<<'\n'<<"2. schimba numele unui folder/fisier"<<'\n'<<"3. gasirea adresei unui fisier/folder"<<'\n';
    cout<<"4. gasirea adresei a tuturor fisierelor/folderelor cu acelasi nume"<<'\n'<<"5. Stergerea unui folder/fisier"<<'\n'<<"6. Ce contine un fisier"<<'\n';
    cout<<"7. Tot ce contine un fisier (subfoldere)"<<'\n'<<"8. Deschide un folder"<<'\n'<<"9. Adauga un fisier"<<'\n';
    while (cin>>caz){
    if (caz==1){
        afis();
    }
    else if (caz==2){
    cout<<"Numele/adresa folderului ce trebuie schimbat:";
    cin.get();
    cin.getline(hmm,200);
    cout<<"Noul nume al folderului:";
    cin.getline(oh,200);
    if (e_adr(hmm)==0)
        findpath(hmm);
    else strcpy(pathm,hmm);
    char pathmb[200];
    strcpy(pathmb,pathm);
    int cnp=strlen(pathm);
    while (pathmb[cnp]!='/')
        pathmb[cnp--]=NULL;
    ppathmb=cnp+1;
    for (int i=0; oh[i]; ++i){
        pathmb[++cnp]=oh[i];
    }
    pathmb[++cnp]=NULL;
    redenumire(pathm,pathmb);
    } else if (caz==3){
        cout<<"Numele folderului ce trebuie cautat:";
        cin.get();
        cin.getline(hmm,200);
        findpath(hmm);
        if (okk==1)
            cout<<pathm;
    }else if (caz==4){
        cout<<"Numele folderului ce trebuie cautat:";
        cin.get();
        cin.getline(hmm,200);
        allfiles=0;
        findpath(hmm);
    } else if (caz==5){
        cout<<"Numele/adresa folderului ce trebuie sters:";
        cin.get();
        cin.getline(hmm,200);
        findpath(hmm);
        if (okk){
            cout<<pathm<<'\n';
            CloseHandle(pathm);
            delete_fisier(ischimb+1, ischimb);
            findpath(hmm);
            if (RemoveDirectoryA(pathm) == 0)
                DeleteFileA(pathm);
            cout<<"File and subfolders deleted successfully";
        }
    } else if (caz==6){
        cout<<"Numele/adresa folderului ce trebuie cautat:";
        cin.get();
        cin.getline(hmm,200);
        ce_este_in_fisier(hmm);
    } else if (caz==7){
        cout<<"Numele/adresa folderului ce trebuie cautat:";
        cin.get();
        cin.getline(hmm,200);
        totfis=1;
        ce_este_in_fisier(hmm);
        totfis=0;
    } else if (caz==8){
        cout<<"Numele/adresa folderului ce trebuie deschis:";
        cin.get();
        cin.getline(hmm,200);
        if (e_adr(hmm))
            strcpy(pathm, hmm);
        else findpath(hmm);
        if (ShellExecute(NULL, "open", pathm, NULL, NULL, SW_SHOWDEFAULT)==0)
            cout<<"Nu exista fisierul/adresa cu numele acesta";
    }else if (caz==9){
        cout<<"Numele fisierului care trebuie adaugat:";
        cin.get();
        cin.getline(hmm,200);
        cout<<"Numele/adresa folderului unde trebuie adaugat:";
        cin.getline(oh,200);
        add(oh);
    }else if (caz==10){



    } else break;
    cout<<'\n'<<'\n'<<"Ce mai vreti sa faceti? "<<'\n'<<'\n'<<"1. afisarea matricei"<<'\n'<<"2. schimba numele unui folder/fisier"<<'\n'<<"3. gasirea adresei unui fisier/folder"<<'\n';
    cout<<"4. gasirea adresei a tuturor fisierelor/folderelor cu acelasi nume"<<'\n'<<"5. Stergerea unui folder/fisier"<<'\n'<<"6. Ce contine un fisier"<<'\n';
    cout<<"7. Tot ce contine un fisier (subfoldere)"<<'\n'<<"8. Deschide un folder"<<'\n';
