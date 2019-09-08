# thead unsafe version
Hello* StaticGetHello()
{
    static Hello* obj=nullptr;
    if(!obj)
    {
        obj=...
    }
    return obj;
}

# thead safe version
Hello& StaticGetHello()
{
    static Hello obj(...);
    return obj;
}
