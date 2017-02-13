using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace CS451Compiler
{
    class Program
    {
        static void Main(string[] args)
        {
            float f = 1;
            if (true) { }
            int i = 1;
            string file = File.ReadAllText(Console.ReadLine());
            LexicalAnalyzer lexi = new LexicalAnalyzer(file.ToCharArray());
            while (lexi.AnalyzeNextlexeme())
            {
                Console.WriteLine(lexi.tokenType.ToString() + ":" + lexi.lexeme);
            }
        }
    }
}
