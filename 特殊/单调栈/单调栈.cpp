namespace MonoStack
{
    stack<int> st;
    bool cmp=true;//true升序,false降序
    void build(int *a, int n)
    {
        n++;
        if(cmp)
        {
            a[n]=INT_MAX;
        }
        else
        {
            a[n]=INT_MIN;//为了保证所有元素都能出来，要有一个极值。
        }
        for(int i=1; i<=n; i++)
        {
            if (st.empty() || st.top()==a[i] || (st.top()-a[i]>0)==cmp)
            {
                st.push(a[i]);
            }
            else
            {
                while(!st.empty() && ((st.top()-a[i]>0)!=cmp))
                {
                    st.pop();
                    //更新答案
                }
                st.push(a[i]);
            }
        }
    }
}