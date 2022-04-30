#include<bits/stdc++.h>
using namespace std;
int label,show_steps,steps=1;

class Point
{

    int x;int y;
    public:
        Point()
        {
            x=0;
            y=0;
        }
        Point(int X,int Y)
        {
            x = X;
            y = Y;
        }
        int operator[](const int & i)
        {
            return ((i==0)? x:y);
        }
};

vector<Point> Convex_Hull;

int side_of_point(Point &p,Point &p1,Point &p2)
{
    int ch = (p[1] - p1[1]) * (p2[0] - p1[0]) - (p2[1] - p1[1]) * (p[0] - p1[0]);
    if(ch > 0)
        return 1;
    else if(ch<0)
        return -1;
    else 
        return 0;
}

pair<int,int> Sort(vector<Point> &v,Point mnx,Point mxx,int s,int e)
{
    int n = e-s + 1;
    vector<Point> t1,t2,t3;
    for(int i=s;i<=e;i++)
    {
        int side = side_of_point(v[i],mnx,mxx);
        if(side == 1)
            t1.push_back(v[i]);
        else if(side == 0)
            t2.push_back(v[i]);
        else
            t3.push_back(v[i]);
    }
    int l1 = t1.size(),
        l2 = t2.size(),
        l3 = t3.size() ;
    for(int i=s;i<s+l1;i++)
        v[i] = t1[i-s];
    for(int i=s+l1;i<s+l1+l2;i++)
        v[i] = t2[i-s-l1];
    for(int i=s+l1+l2;i<(s+l1+l2+l3);i++)
        v[i] = t3[i-s-l1-l2];
    
    pair<int,int> p;
    p.first  = s+l1-1;
    p.second = e-l3+1;
    return p;
}

int Dis_frm_line(Point &p,Point &p1,Point &p2)
{
    return abs((p[1] - p1[1]) * (p2[0] - p1[0]) - (p2[1] - p1[1]) * (p[0] - p1[0])) ;
}

void display(vector<Point> Points)
{
    int n = Points.size();
    int r=0;
    for(auto P:Points)
    {
        if(r < max(abs(P[0]),abs(P[1])))
        r  = max(abs(P[0]),abs(P[1]));
    }
    r++;
    string s="|";
    
    for(int i=0;i<r;i++)
    {
        s+="  .";
        s = ".  " + s;
    }
    vector<string> v(2*r+1,s);
    for(int i=0;i<v[r].size();i++)
    v[r][i] = '-';
    v[r][3*r] = '|';
    int nextletter = 0;
    int ox = 3*r,oy = r;
    for(auto p:Points)
    {
        if(!label)
        v[oy-p[1]][ox+3*p[0]] = 'o';
        else
        {
            v[oy-p[1]][ox+3*p[0]] = 'o';
            v[oy-p[1]][ox+3*p[0]+1] = 65 + ((nextletter++)%26);
        }
    }
    cout<<endl;
    for(auto s:v)
    cout<<s<<endl;
    cout<<endl;
    
}

void ConvexHull(vector<Point> &v,Point mnx,Point mxx,int side,int s,int e)
{
    int n = v.size();
    Point mx_dis_p ;
    bool found=false;
    int mx_dis = 0;

    for(int i=s;i<=e;i++)
    {
        int curr_dis = Dis_frm_line(v[i],mnx,mxx);
        if(curr_dis > mx_dis)
        {
            found = true;
            mx_dis_p = v[i];
            mx_dis = curr_dis;
        }
    }

    if(found)
    {
        Convex_Hull.push_back(mx_dis_p);
        if(show_steps)
	{	cout<<"Step "<<(steps++)<<"\n";
		display(Convex_Hull);
	}
        pair<int,int> p = Sort(v,mnx,mx_dis_p,s,e);
        if(side==1)
        {
            if(p.first >= s) 
            ConvexHull(v,mnx,mx_dis_p,1,s,p.first);
            p = Sort(v,mx_dis_p,mxx,s,e);
            if(p.first >= s)
            ConvexHull(v,mx_dis_p,mxx,1,s,p.first);
        }
        else if(side==-1)
        {
            if(p.second <= e) 
            ConvexHull(v,mnx,mx_dis_p,-1,p.second,e);
            p = Sort(v,mx_dis_p,mxx,s,e);
            if(p.second <= e)
            ConvexHull(v,mx_dis_p,mxx,-1,p.second,e);
        }
    }

}

void getConvexHull(vector<Point> &Points)
{
    int n = Points.size();
    if(n<3)
    {
        cout<<"Convex Hull can be made only if there are at least three non collinear points\n";
        return;
    }

    Point mnx=Points[0],mxx = Points[0];
    for(Point p: Points)
    {
        if(p[0] < mnx[0])
        mnx = p;
        else if(p[0] > mxx[0])
        mxx = p;
    }
    Convex_Hull.push_back(mnx);
    Convex_Hull.push_back(mxx);
    pair<int,int> p;
    p = Sort(Points,mnx,mxx,0,n-1);
    if(!(p.first == -1 && p.second == n) && show_steps)
    {
	cout<<"Step "<<(steps++)<<"\n";
	display(Convex_Hull);
    }
    if(p.first >= 0)
    ConvexHull(Points,mnx,mxx,1,0,p.first);
    if(p.second < n)
    ConvexHull(Points,mnx,mxx,-1,p.second,n-1);

    set<pair<int,int>> s;
    for(Point p:Convex_Hull)
    s.insert({p[0],p[1]});
    if(s.size()<3)
    {
        cout<<"Convex Hull can be made only if there are at least three non collinear points\n";
        return;
    }

    cout<<"The coordinates of points of ConvexHull are :-\n";
    for(auto it=s.begin();it != s.end();it++)
    cout<< (*it).first << " " << (*it).second << endl;

    cout<<"\nThis is the Convex Hull\n";
    display(Convex_Hull);

}

int main()
{
    int n;cout<<"Enter the no. of points : ";cin>>n;
    Point p;int x,y;
    vector<Point> v;cout<<"Enter coordinates of Points :-\n";
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        p = Point(x,y);
        v.push_back(p);
    }
    cout<<"Do you want to name the points in graph [1 = yes,0 = no] : ";cin>>label;
    cout<<"Given Points\n";
    display(v);
    cout<<"Do you want to show graph for each step [1 = yes,0 = no] : ";cin>>show_steps;

    getConvexHull(v);    
    return 0;
}


