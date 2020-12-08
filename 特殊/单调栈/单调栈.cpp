namespace MonoStack
{
    stack<int> st;
    bool cmp=true;//true����,false����
    void build(int *a, int n)
    {
        n++;
        if(cmp)
        {
            a[n]=INT_MAX;
        }
        else
        {
            a[n]=INT_MIN;//Ϊ�˱�֤����Ԫ�ض��ܳ�����Ҫ��һ����ֵ��
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
                    //���´�
                }
                st.push(a[i]);
            }
        }
    }
}