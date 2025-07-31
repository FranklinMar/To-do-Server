using Grpc.Net.Client;
using System.Configuration;
using System.Data;
using System.Net;
using System.Threading.Channels;
using System.Windows;
using System.Text.RegularExpressions;
using ToDoService.V1;

namespace To_doClient
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public ToDoService.V1.ToDoService.ToDoServiceClient Client { get; private set; }
        public App(string address = "127.0.0.1", uint port = 50055) {
            // Initialize the application
            InitializeComponent();

            var Regex = new Regex("^(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
            if (!Regex.IsMatch(address))
            {
                throw new ArgumentException("Invalid IP address format.");
            }
            var Channel = GrpcChannel.ForAddress($"http://{address}:{port}");
            Client = new(Channel);
        }
    }

}
