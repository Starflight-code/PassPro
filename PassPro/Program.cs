// See https://aka.ms/new-console-template for more information
Console.Write("\nEnter a number: ");
string? userInput = Console.ReadLine();
if (userInput == null)
{
    userInput = "";
}
int userNumber;
try
{
    userNumber = int.Parse(userInput);
}
catch
{
    throw new Exception("Number is not a number");
}
if (userNumber < 0)
{
    throw new Exception("Number is negative");
}
int outStars;
for (int i = 0; i < userNumber; i++)
{
    outStars = i * 2 + 1;
    for (int j = 0; j < outStars; j++)
    {
        Console.Write("*");
    }
    Console.WriteLine();
}
