בס"ד

* ID: 212051007 
* Mail: mayrozen45@gmail.com
# מטלה 4 - תכנות מערכות 2:
מטלה זו הייתה על עצים - STL, Templates, and Iterators.
אפרט כעת כיצד מימשתי את המחלקות והאופרטורים הנדרשים וכן אפרט על השיקולים לכך.

## מחלקת Node
מחלקה זו מהווה Node (צומת) בעץ. לכל צומת קיים ערך מסוג גנרי T בשם value ווקטור המחזיק pointers לצמתים שתחתיו בשם children.
בנוסף קיימות הפונקציות get_value(), add_childe().

## מחלקת Tree
מחלקה זו מהווה את העץ עצמו. המחלקה מורכבת משורש מסוג מצביע לNode וכמות מקסימלית של ילדים המוגדרת על ידי K שמוגדר בעזרת template .template זהו מבנה כללי שמאפשר ליצור קונטיינרים, ובמקרה כאן - עצים, עם סוגי נתונים שונים ומספר ילדים מקסימלי מותאם אישית בצורה יעילה וללא צורך בחזרתיות על קוד. אצלינו, במידה ולא מוכנס ערך אחר, K מוגדר להיות 2 כנדרש באופן הבא:
template<typename T, int K = 2>
כמו כן, מחלקה זו מכילה בתוכה את כלל האופרטורים שניתן לבצע על העץ כאשר כל אחד מן האופרטורים מהווה class בפני עצמו שמכילה את הפעולות שעושה האופרטור:
        
        class PreOrderIterator
        class PostOrderIterator
        class InOrderIterator
        class BFSIterator
        class DFSIterator
        class HeapIterator

כעת אפרט על כל אחד מהאופרטורים:

### PreOrderIterator 
איטרטור הסורק את העץ בצורה הבאה: צומת נוכחית -> תת עץ שמאלי -> תת עץ ימני. במידה והעץ אינו בינארי האיטרטור יעבור על העץ ע"י DFS כפי שנדרש.
במימוש האיטרטור השתמשתי במחסנית אליה הוצאתי והכנסתי איברים על מנת לשלוט בסדרם כך שהמעבר על העץ יהיה בצורה המבוקשת.

### PostOrderIterator
איטרטור הסורק את העץ בצורה הבאה: תת עץ שמאלי -> תת עץ ימני -> צומת נוכחית. במידה והעץ אינו בינארי האיטרטור יעבור על העץ ע"י DFS כפי שנדרש.
גם כאן השתמשתי במחסנית.

### InOrderIterator
איטרטור הסורק את העץ בצורה הבאה: תת עץ שמאלי -> צומת נוכחית -> תת עץ ימני.  במידה והעץ אינו בינארי האיטרטור יעבור על העץ ע"י DFS כפי שנדרש.
גם כאן השתמשתי במחסנית.
    
### BFSIterator
סריקת העץ לרוחב (משמאל לימין) (עובד על עץ כללי). על מנת לממש את סריקה זו נעזרתי בתור. סריקה זו היא סריקה לרוחב.
האלגוריתם מתחיל לרוץ משורש העץ אותו מכניסים לתור queue ראשון. כל עוד התור אינו ריק, מסירים את הצומת הקדמי מהתור וסורקים את השכנים שלו.
אם מצאנו שכן שטרם נסרק ולא נמצא בתור, אז מוסיפים אותו לתור. כך לבסוף התור מכיל את האיברים אשר עברנו עליהם (כל איברי העץ) בסדר הנדרש.

### DFSIterator
סריקת העץ בעזרת אלגוריתם DFS (עובד על עץ כללי). בשביל לממש את סריקה זו נעזרתי במחסנית. סריקה זו היא סריקה לעומק.
תחילה מכניסים את שורש העץ למחסנית. בוחרים מסלול מסוים ומתחילים לרוץ עליו עד שנגיע לסופו (NULL). כל איבר ש"פגשנו" נכנס לתוך המחסנית. כך עוברים על כלל המסלולים עד שלבסוף מקבילים מחסנית שמכילה את האיברים של העץ בסדר הנדרש.

### HeapIterator
באיטרטור זה הפכנו את העץ לערימת מינימום: עץ שכל צומת בו קטן יותר מהצמתים שתחתיו (באופן זהה ניתן גם להפוך לערימת מקסימום). באיטרטור זה השתמשתי בפונקציה void siftDown(size_t i, size_t n) שבעזרתה השוויתי בין ערכי הצמתים בעץ וסידרתי אותו מחדש, ובפונקציה void fillVector(Node<T>* node) שבעזרתה הכנסתי את איברי העץ למחסנית בסדר הנדרש.

# מחלקת Complex
מחלקה זו מממשת את המספרים המרוכבים. זאת על מנת שנוכל לבצע את הפעולות הנ"ל על עץ המכיל גם ערכים מסוג מספרים מרוכבים.

# מחלקת Test
מחלקה זו אחראית על כלל הבדיקות ובה נמצאים כלל הטסטים.
מבין הבדיקות אותן ביצעתי: בדיקת עץ המכיל 60 ילדים והשמת ערכיו וצמתיו, ביצוע בדיקה על עץ בינארי מסוג int, ביצוע בדיקה על עץ 3-ארי מסוג double, ביצוע בדיקה על עץ 3-ארי מסוג Complex.

# GUI
על מנת לצייר את העץ השתמשתי בsfml הממומשת בתוך מחלקת Tree ונקראת על ידי tree.drow().

# Compilation
פקודות קומפילציה: 
* make
פקודות הרצה:
* ./demo
* ./test

    
      




