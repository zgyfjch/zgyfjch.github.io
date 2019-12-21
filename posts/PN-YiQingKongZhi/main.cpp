#include<cstdio> 
#include<algorithm>
#include<cstring>
#include<cmath>
int N,M;
static const int MAXN=5e4+10;
static const int MAXLOGN =20;
int SHd[MAXN],SNxt[MAXN*2],STo[MAXN*2],SDis[MAXN*2],SCount;
typedef long long ll;
inline void AddEdge(int from,int to,int dis){
	SCount++;
	SNxt[SCount]=SHd[from];
	STo[SCount]=to;
	SDis[SCount]=dis;
	SHd[from]=SCount;
}
ll l,r,mid;
/*
int Dis[MAXN];

void Dfs1(int u,int fa,int road){
	Dis[u]=road;
	for(int i=SHd[u];i;i=SNxt[i])if(STo[i]!=fa){
		Dfs1(STo[i],u,road+SDis[i]);
	}
}ll Dfs2(int u,int fa)
{
	//返回值意义:
		//>0可自保,本地军队还可以走的最大里程数 
		//=0可自保,但军队走不动了或没有本地军队 
		//<0(=-1)不可自保,请求援助 
	//Ans表示军队调过来后,还可以走的里程数(>=0),-1表示无军队
	//for每个儿子
		//如果该儿子可自保
			//如果它的军队能过来就让它来
				//来了以后选个最能走,其他的就地解散 
		//如果不能自保记下来
	//如果有儿子不能自保
		//如果本地没有军队
			//发送援救信号
		//如果有军队
			//return 
	//如果儿子都能自保
		//如果本地军队走不动了或没有本地军队 返回0
		//否则返回本地军队还能走多远 
	ll Ans=(ll)Flag[u]?mid:-1;
	int DoesSonNeedHelp=false;
	for(int i=SHd[u];i;i=SNxt[i])if(STo[i]!=fa){
		ll tmp=Dfs2(STo[i],u);
		if(tmp>=0){
			if(tmp-SDis[i]>=0)
				Ans=std::max(tmp-SDis[i],Ans);
		}
		else DoesSonNeedHelp=true;
	}
	if(DoesSonNeedHelp=false)if(Ans<0)Ans=0;
	return Ans;
}
int Check(){
	for(int i=SHd[1];i;i=SNxt[i]){
		if(Dfs2(STo[i],1)==-1){
			return false;
		}
	}
	return true;
}
int Arrmy[MAXN],Flag[MAXN];*/
int Arrmy[MAXN];
int Cost[MAXN];
int fa[MAXN][MAXLOGN];
ll dis[MAXN][MAXLOGN];
void Dfs1(int u){
	for(int i=1;i<MAXLOGN;i++){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		dis[u][i]=dis[u][i-1]+dis[fa[u][i-1]][i-1];
	}
	for(int i=SHd[u];i;i=SNxt[i])if(STo[i]!=fa[u][0]){
		fa[STo[i]][0]=u;
		dis[STo[i]][0]=SDis[i];
		Dfs1(STo[i]);
	}
}
int Now[MAXN],BeSet[MAXN];
ll Last[MAXN];
int SonChecker(int u){
	if(BeSet[u])return true;
	bool flag=0;
	for(int i=SHd[u];i;i=SNxt[i])if(STo[i]!=fa[u][0]){
		flag=1;
		if(!SonChecker(STo[i]))return 0;
	}
	return flag;
}
int InNeed[MAXN],Helper[MAXN],Top,HelperTop;
int MinnHelper[MAXN];
int Check(){
	Top=HelperTop=0;
	memset(MinnHelper,0,sizeof(MinnHelper));
	memset(BeSet,0,sizeof(BeSet));
	int SonSize=0;
	for(int i=1;i<=M;i++)
	{
		Now[i]=Arrmy[i];
		Last[i]=mid;
		for(int j=MAXLOGN-1;j>=0;j--){
			if(Last[i]>=dis[Now[i]][j]&&fa[Now[i]][j]>1){
				Last[i]-=dis[Now[i]][j];
				Now[i]=fa[Now[i]][j];
				}
		}
		BeSet[Now[i]]++;
	}
	for(int i=SHd[1];i;i=SNxt[i]){
		SonSize++;
		if(!SonChecker(STo[i])){
			InNeed[++Top]=SDis[i];
		}
	}
	Helper[0]=0x7f7f7f7f;
	if(Top<=0)return true;
	std::sort(InNeed+1,InNeed+Top+1);
	for(int i=1;i<=M;i++)if(fa[Now[i]][0]==1){
		if(Last[i]>=dis[Now[i]][0]){
			Helper[++HelperTop]=Last[i]-dis[Now[i]][0];
			if(Helper[MinnHelper[Now[i]]]>Helper[HelperTop])MinnHelper[Now[i]]=HelperTop;
		}
	}
	for(int i=SHd[1];i;i=SNxt[i]){
		Helper[MinnHelper[i]]=0;
	}
	if(HelperTop<Top)return false;
	std::sort(Helper+1,Helper+1+HelperTop);
	int Start=1;
	Start=HelperTop-(SonSize-Top);
	while(HelperTop>=Start&&Top>0){
		if(Helper[HelperTop]<InNeed[Top])return false;
		Top--,HelperTop--;
	}
	return true;
}
int main(void)
{
	freopen("in")
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(u,v,w);
		AddEdge(v,u,w);
		r+=(ll)w;
	}
	scanf("%d",&M);
	for(int i=1;i<=M;i++)
	{
		scanf("%d",Arrmy+i);
	}
	ll Ans=0x7f7f7f7f;
	Dfs1(1);
	while(l<=r){
		printf("!%d\n",mid);
		mid=(l+r)/2;
		if(Check())
		{
			Ans=std::min(Ans,mid);
			r=mid-1;
		}
		else l=mid+1;
	}
	if(Ans==0x7f7f7f)Ans=-1;
	printf("%lld\n",Ans);
	return 0;
}
