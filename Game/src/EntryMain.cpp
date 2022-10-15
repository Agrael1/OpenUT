#include <Game/App.h>
#include <iostream>
#include <ThreadModel.h>
#include <Framework/Exceptions.h>

winrt::apartment_context ver::ThreadModel::ui_tread;

int main()
{
    struct a {
        a() { winrt::init_apartment(); }
        ~a(){winrt::uninit_apartment();}
    }lifetime;
    ver::ThreadModel model;

    try
    {
        UT::App a;
        a.InitializeAsync().get();
        return a.Go();
    }
    catch (const winrt::hresult_error& e)
    {
        std::wcerr << e.message().c_str();
    }
    catch (const ver::gfx_exception& e)
    {
        std::cerr << e.what();
    }
    return -1;
}