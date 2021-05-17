using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Drawing;
using System.Runtime.InteropServices;

namespace csharp실험용
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            var image = new DDSImage();
            var bmp = image.Load("C:/Users/dh045/Desktop/Chimera/_Assets/Texture/Effect/Decal/Decal.dds");
            MyImage.Source = bmp;
            //DevIL.DevIL.LoadBitmap(@"C:\Users\dh045\Desktop\Chimera\_Assets\Texture\Brush\Circle.dds");

        }
    }
}
