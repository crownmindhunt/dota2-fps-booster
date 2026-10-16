using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Dota2FpsBooster.Shell;

internal static class Program
{
    [DllImport("tweaker-core.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int d2fb_apply_tweak(string id);

    [STAThread]
    static int Main(string[] args)
    {
        if (args.Length >= 2 && args[0] == "--apply")
        {
            var rc = d2fb_apply_tweak(args[1]);
            Console.WriteLine(rc == 0 ? "applied" : "failed");
            return rc;
        }

        Console.WriteLine("dota2-fps-booster shell v0.9.4");
        Console.WriteLine("launch the WPF UI with no arguments");
        return 0;
    }
}