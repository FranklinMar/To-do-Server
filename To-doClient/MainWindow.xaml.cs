using System.Collections.ObjectModel;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ToDoService.V1;
using ToDo_Service = ToDoService.V1.ToDoService;

namespace To_doClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly ToDo_Service.ToDoServiceClient Client;
        public ObservableCollection<BindableToDo> ToDos { get; set; }
        public MainWindow()
        {
            InitializeComponent();
            ToDos = [];
            DataContext = this;
            Client = ((App)Application.Current).Client;
        }

        private async void Window_Loaded(object sender, RoutedEventArgs e)
        {
            GetListReq ListReq = new();
            var ListRes = await Client.GetListAsync(ListReq);
            foreach (var todo in ListRes.ToDo)
            {
                BindableToDo Todo = new(todo);
                Todo.StatusChanged += UpdateTodo_Click;
                ToDos.Add(Todo);
            }
            StreamUpdateChangeReq StreamReq = new();
            //Client.StreamUpdateChange(StreamReq, StreamUpdate);
            /*Client.StreamUpdateChange(StreamReq, (response) =>
            {
                if (response.Todo != null)
                {
                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        ToDos.Add(response.Todo);
                    });
                }
            });*/
            using var Call = Client.StreamUpdateChange(StreamReq);
            while (await Call.ResponseStream.MoveNext(CancellationToken.None))
            {
                var update = Call.ResponseStream.Current;
                if (update.Todo != null)
                {
                    var Todo = ToDos.FirstOrDefault(todo => todo.Id == update.Todo.Id);
                    if (Todo == null)
                    {
                        BindableToDo todo = new(update.Todo);
                        todo.StatusChanged += UpdateTodo_Click;
                        ToDos.Add(todo);
                    }
                    else
                    {
                        Todo.Description = update.Todo.Description;
                        //Todo.SetStatus(update.Todo.Status);
                        Todo.SetStatusNoUpdate(update.Todo.Status);
                    }
                }
            }
        }

        private void UpdateTodo_Click(object sender, Status status) {
            UpdateItemReq Req = new()
            {
                Todo = ((BindableToDo)sender).GetOriginal()
            };
            Client.UpdateItem(Req);
        }

        /*private async void StreamUpdate(StreamUpdateChangeRes response)
        {
            if (response.Todo != null)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    ToDos.Add(response.Todo);
                });
            }
        }*/

        private void AddToDo_Click(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(NewDescriptionBox.Text))
            {
                AddItemReq Req = new()
                {
                    Description = NewDescriptionBox.Text
                };
                Client.AddItem(Req);
            }
        }
    }
}